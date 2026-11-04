// С любого цифрового или аналогового вывода можно снять максимум 40 мА
// Можно питать максимум 2 светодиода на полную яркость
// Светодиод питается током
// Анод (+) длиннее, чем катод (-)
// Характеристики светодиода:
//    Iпит - ток питания (максимальный ток для светодиода равен 20 мА)
//    Uпад - напряжение падения (зависит от цвета светодиода)
// R = (Vпит - Vпад) / Iпит = (5 - 3) / 0,02 = 100; (увеличивать R можно для настройки яркость, уменьшать нельзя - светодиод может сгореть)

#include <Arduino.h>

constexpr uint8_t BUTTON_PIN = 2;
constexpr uint8_t FIRST_LED_PIN = 4;
constexpr uint8_t SECOND_LED_PIN = 5;

constexpr uint32_t DEBOUNCE_MS = 30;
constexpr uint32_t DOUBLE_CLICK_MS = 350;
constexpr uint32_t LONG_PRESS_MS = 700;
constexpr uint32_t BLINK_INTERVAL_MS = 80;

enum class ButtonEvent {
  None,
  SingleClick,
  DoubleClick,
  HoldStarted,
  HoldEnded
};

struct ButtonState {
  bool rawPressed = false;
  bool pressed = false;
  bool holding = false;
  bool waitingForSecondClick = false;

  uint32_t rawChangedAt = 0;
  uint32_t pressedAt = 0;
  uint32_t releasedAt = 0;
};

struct LedState {
  bool firstOn = false;
  bool secondOn = false;
  bool blinking = false;
  bool firstBlinkOn = true;

  uint32_t blinkChangedAt = 0;
};

ButtonState button;
LedState leds;

ButtonEvent readButtonEvent(uint32_t now);
bool updateDebouncedButton(uint32_t now);
ButtonEvent handleButtonPress();
ButtonEvent handleButtonRelease();
ButtonEvent detectTimedEvent(uint32_t now);
void handleButtonEvent(ButtonEvent event);
void updateLeds(uint32_t now);

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(FIRST_LED_PIN, OUTPUT);
  pinMode(SECOND_LED_PIN, OUTPUT);

  digitalWrite(FIRST_LED_PIN, LOW);
  digitalWrite(SECOND_LED_PIN, LOW);
}

void loop() {
  handleButtonEvent(readButtonEvent(millis()));
  updateLeds(millis());
}

void handleButtonEvent(ButtonEvent event) {
  switch (event) {
    case ButtonEvent::SingleClick:
      leds.firstOn = !leds.firstOn;
      break;

    case ButtonEvent::DoubleClick:
      leds.secondOn = !leds.secondOn;
      break;

    case ButtonEvent::HoldStarted:
      leds.blinking = true;
      leds.firstBlinkOn = true;
      leds.blinkChangedAt = millis();
      break;

    case ButtonEvent::HoldEnded:
      leds.blinking = false;
      break;

    case ButtonEvent::None:
      break;
  }
}

void updateLeds(uint32_t now) {
  if (leds.blinking &&
      now - leds.blinkChangedAt >= BLINK_INTERVAL_MS) {
    leds.firstBlinkOn = !leds.firstBlinkOn;
    leds.blinkChangedAt = now;
  }

  const bool firstOn =
      leds.blinking ? leds.firstBlinkOn : leds.firstOn;

  const bool secondOn =
      leds.blinking ? !leds.firstBlinkOn : leds.secondOn;

  digitalWrite(FIRST_LED_PIN, firstOn ? HIGH : LOW);
  digitalWrite(SECOND_LED_PIN, secondOn ? HIGH : LOW);
}

ButtonEvent readButtonEvent(uint32_t now) {
  if (updateDebouncedButton(now)) {
    return button.pressed
        ? handleButtonPress()
        : handleButtonRelease();
  }

  return detectTimedEvent(now);
}

bool updateDebouncedButton(uint32_t now) {
  const bool rawPressed = digitalRead(BUTTON_PIN) == LOW;

  if (rawPressed != button.rawPressed) {
    button.rawPressed = rawPressed;
    button.rawChangedAt = now;
  }

  if (now - button.rawChangedAt < DEBOUNCE_MS) {
    return false;
  }

  if (button.pressed == button.rawPressed) {
    return false;
  }

  button.pressed = button.rawPressed;
  return true;
}

ButtonEvent handleButtonPress() {
  button.pressedAt = button.rawChangedAt;

  // Позднее нажатие начинает новый клик.
  // Предыдущий клик в этом случае считается одиночным.
  if (button.waitingForSecondClick &&
      button.pressedAt - button.releasedAt >= DOUBLE_CLICK_MS) {
    button.waitingForSecondClick = false;
    return ButtonEvent::SingleClick;
  }

  return ButtonEvent::None;
}

ButtonEvent handleButtonRelease() {
  // Отпускание после удержания не считается кликом.
  if (button.holding) {
    button.holding = false;
    return ButtonEvent::HoldEnded;
  }

  if (button.waitingForSecondClick) {
    button.waitingForSecondClick = false;
    return ButtonEvent::DoubleClick;
  }

  button.waitingForSecondClick = true;
  button.releasedAt = button.rawChangedAt;

  return ButtonEvent::None;
}

ButtonEvent detectTimedEvent(uint32_t now) {
  if (button.pressed &&
      button.rawPressed &&
      !button.holding &&
      now - button.pressedAt >= LONG_PRESS_MS) {
    button.holding = true;

    // Удержание отменяет ожидающий одиночный клик.
    button.waitingForSecondClick = false;

    return ButtonEvent::HoldStarted;
  }

  // Ждём завершения подавления дребезга второго нажатия,
  // прежде чем признать предыдущий клик одиночным.
  if (!button.pressed &&
      !button.rawPressed &&
      button.waitingForSecondClick &&
      now - button.releasedAt >= DOUBLE_CLICK_MS) {
    button.waitingForSecondClick = false;
    return ButtonEvent::SingleClick;
  }

  return ButtonEvent::None;
}