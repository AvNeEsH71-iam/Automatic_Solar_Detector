/*
 * Automatic Dual-Axis Solar Tracker
 * PHY312 — IISER Mohali | Group 3
 * Tisha (MS23211), Brahamjot (MS23212), Avneesh (MS23249)
 *
 * Features:
 *   - 4x LDR quadrant sensing
 *   - Proportional control with dead-band
 *   - LCD display showing live angles + errors
 *   - Green LED = tracking active
 */

#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ── Pins ─────────────────────────────────────────────────────
#define LDR_TL  A0    // Top-Left
#define LDR_TR  A1    // Top-Right
#define LDR_BL  A2    // Bot-Left
#define LDR_BR  A3    // Bot-Right
#define SERVO_AZ 9    // Azimuth  (left/right)
#define SERVO_EL 10   // Elevation (up/down)
#define LED_PIN  8    // Tracking indicator LED

// ── Tuning ───────────────────────────────────────────────────
const float KP        = 0.05;
const int   DEAD_BAND = 30;
const int   MIN_ANG   = 10;
const int   MAX_ANG   = 170;

// ── Objects ──────────────────────────────────────────────────
Servo servoAz, servoEl;
LiquidCrystal_I2C lcd(0x27, 16, 2);

float az = 90.0, el = 90.0;
int   loopCount = 0;

void setup() {
  servoAz.attach(SERVO_AZ);
  servoEl.attach(SERVO_EL);
  servoAz.write(90);
  servoEl.write(90);

  pinMode(LED_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Solar Tracker ");
  lcd.setCursor(0, 1);
  lcd.print(" Group 3 PHY312 ");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);
  Serial.println("Time\tV1\tV2\tV3\tV4\teAZ\teEL\tAZ\tEL");
}

void loop() {
  // ── Read sensors ─────────────────────────────────────────
  int v1 = analogRead(LDR_TL);
  int v2 = analogRead(LDR_TR);
  int v3 = analogRead(LDR_BL);
  int v4 = analogRead(LDR_BR);

  // ── Compute errors ───────────────────────────────────────
  int e_az = (v1 + v3) - (v2 + v4);
  int e_el = (v1 + v2) - (v3 + v4);

  // ── Control ──────────────────────────────────────────────
  bool tracking = false;

  if (abs(e_az) > DEAD_BAND) {
    az = constrain(az + KP * e_az, MIN_ANG, MAX_ANG);
    servoAz.write((int)az);
    tracking = true;
  }
  if (abs(e_el) > DEAD_BAND) {
    el = constrain(el + KP * e_el, MIN_ANG, MAX_ANG);
    servoEl.write((int)el);
    tracking = true;
  }

  // ── LED indicator ────────────────────────────────────────
  digitalWrite(LED_PIN, tracking ? HIGH : LOW);

  // ── LCD display ──────────────────────────────────────────
  lcd.setCursor(0, 0);
  lcd.print("AZ:");
  lcd.print((int)az);
  lcd.print((char)223);   // degree symbol
  lcd.print("  EL:");
  lcd.print((int)el);
  lcd.print((char)223);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("eAZ:");
  if (e_az >= 0) lcd.print("+");
  lcd.print(e_az);
  lcd.print(" eEL:");
  if (e_el >= 0) lcd.print("+");
  lcd.print(e_el);
  lcd.print("   ");

  // ── Serial monitor (tab-separated for data logging) ──────
  loopCount++;
  Serial.print(loopCount * 100);  Serial.print("\t");
  Serial.print(v1); Serial.print("\t");
  Serial.print(v2); Serial.print("\t");
  Serial.print(v3); Serial.print("\t");
  Serial.print(v4); Serial.print("\t");
  Serial.print(e_az); Serial.print("\t");
  Serial.print(e_el); Serial.print("\t");
  Serial.print(az, 1); Serial.print("\t");
  Serial.println(el, 1);

  delay(100);
}