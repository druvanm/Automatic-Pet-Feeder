#define BLYNK_TEMPLATE_ID "TMPL3M0MadnLu"
#define BLYNK_TEMPLATE_NAME "Sai ram"
#define BLYNK_AUTH_TOKEN "BeZ6vXY2Z8tm2rl3uJG5CXIXdXtAF9mD"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// Blynk authentication token
char auth[] = "BeZ6vXY2Z8tm2rl3uJG5CXIXdXtAF9mD";

// WiFi credentials
char ssid[] = "Druva";
char pass[] = "12345678";

// Pin Definitions
Servo myServo;
const int servoPin = D4;    // Change as per your connection
const int buzzerPin = D2;   // Connect the buzzer to D2
int sweepFlag = 0;          // To track the sweep state
int angle = 0;              // Initial servo angle

// Blynk Virtual Pin
#define V0 0   // Switch widget in Blynk app

// Blynk Write Function
BLYNK_WRITE(V0)
{
    sweepFlag = param.asInt();   // Read switch state (1 for ON, 0 for OFF)

    // Control the buzzer based on switch state
    if (sweepFlag)
    {
        digitalWrite(buzzerPin, HIGH);   // Turn on buzzer
    }
    else
    {
        digitalWrite(buzzerPin, LOW);    // Turn off buzzer
    }
}

// Sweep function
void sweepServo()
{
    for (angle = 0; angle <= 180; angle++)
    {
        if (!sweepFlag) return;   // Stop sweeping if switch is OFF
        myServo.write(angle);
        delay(15);
    }

    for (angle = 180; angle >= 0; angle--)
    {
        if (!sweepFlag) return;   // Stop sweeping if switch is OFF
        myServo.write(angle);
        delay(15);
    }
}

void setup()
{
    // Initialize serial monitor
    Serial.begin(115200);

    // Setup servo
    myServo.attach(servoPin);
    myServo.write(90);   // Set servo to middle position

    // Setup buzzer
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);   // Ensure buzzer is off initially

    // Initialize Blynk
    Blynk.begin(auth, ssid, pass);

    // Debug messages
    Serial.println("ESP8266 and Blynk are ready.");
}

void loop()
{
    Blynk.run();   // Run Blynk

    if (sweepFlag)
    {
        sweepServo();
    }
}