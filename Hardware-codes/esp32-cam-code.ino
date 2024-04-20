// #include <WebServer.h>
#include <WiFi.h>
#include <esp32cam.h>
#include <HTTPClient.h> // Add this line
#include "base64.h"    // Add this line
// #include <ESP32Servo.h>



const char* WIFI_SSID = "MAHAKAL";
const char* WIFI_PASS = "sateri456";

int LED_PIN = 4;

// const int button1Pin = 0; // Pin number where the button is connected
const int button2Pin = 12; // Pin number where the button is connected

// Servo servo; // Create a servo object
// const int servoPin = 2; // Pin number where the servo signal wire is connected


// WebServer server(80);

static auto loRes = esp32cam::Resolution::find(320, 240);
static auto midRes = esp32cam::Resolution::find(350, 530);
static auto hiRes = esp32cam::Resolution::find(800, 600);

unsigned long previousMillis = 0;
const long interval = 40000; // Interval to upload image (40 seconds)

// Function to capture and upload the image
void captureAndUpload() {
  digitalWrite(LED_PIN, HIGH); delay(250);// Turn on LED

  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    return;
  }
  delay(100);digitalWrite(LED_PIN, LOW); // Turn off LED

  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
                static_cast<int>(frame->size()));

  // Initialize the HTTP client
  HTTPClient http;

  // Construct the form-data payload
  String formData = "--boundary\r\n";
  formData += "Content-Disposition: form-data; name=\"image\"; filename=\"image.jpg\"\r\n";
  formData += "Content-Type: image/jpeg\r\n\r\n";
  formData += String(reinterpret_cast<char*>(frame->data()), frame->size());
  formData += "\r\n";
  formData += "--boundary--\r\n";

  // Set the content type header
  // http.begin("https://69766b76-41ca-4aa9-80b3-a8823de7fc38-00-se4nro7x7qoo.picard.replit.dev/upload"); //old server
  http.begin("https://f9698e73-3671-48d9-a096-9832ceeffc5f-00-3e2zpfrvccauz.pike.replit.dev/upload");     //new server
  http.addHeader("Content-Type", "multipart/form-data; boundary=boundary");

  // Send the POST request with the form-data payload
  int httpResponseCode = http.POST(formData);

  // Check if the request was successful
  if (httpResponseCode > 0) {
    Serial.printf("Image uploaded successfully. HTTP response code: %d\n", httpResponseCode);

    // Print server response
    String response = http.getString();
    Serial.println("Server response:");
    Serial.println(response);
  } else {
    Serial.printf("Failed to upload image. HTTP error code: %d\n", httpResponseCode);
  }

  // End HTTP connection
  http.end();
}

void handleJpgLo() {
  if (!esp32cam::Camera.changeResolution(loRes)) {
    Serial.println("SET-LO-RES FAIL");
  }
  captureAndUpload(); // Call the function to capture and upload image
}

void handleJpgHi() {
  if (!esp32cam::Camera.changeResolution(hiRes)) {
    Serial.println("SET-HI-RES FAIL");
  }
  captureAndUpload(); // Call the function to capture and upload image
}

void handleJpgMid() {
  if (!esp32cam::Camera.changeResolution(midRes)) {
    Serial.println("SET-MID-RES FAIL");
  }
  captureAndUpload(); // Call the function to capture and upload image
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  // servo.attach(servoPin); // Attach the servo to the specified pin
  // servo.write(90);delay(1000); // Wait for 1 second

  // pinMode(button1Pin, INPUT_PULLUP); // Configure the button pin as input with internal pull-up resistor
  pinMode(button2Pin, INPUT_PULLUP); // Configure the button pin as input with internal pull-up resistor


  Serial.println();
  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);

    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println("  /cam-lo.jpg");
  Serial.println("  /cam-hi.jpg");
  Serial.println("  /cam-mid.jpg");

  // server.on("/cam-lo.jpg", handleJpgLo);
  // server.on("/cam-hi.jpg", handleJpgHi);
  // server.on("/cam-mid.jpg", handleJpgMid);

  // server.begin();
}

void loop() {
  // unsigned long currentMillis = millis();
  // if (currentMillis - previousMillis >= interval) {
  //   previousMillis = currentMillis;
  //   handleJpgLo(); // Upload image with cam-lo.jpg endpoint
  // }

  // int buttonState1 = digitalRead(button1Pin); // Read the state of the button
  // Serial.print("buttonState1: ");Serial.print(buttonState1);

  int buttonState2 = digitalRead(button2Pin); // Read the state of the button
  Serial.print("buttonState2: ");Serial.print(buttonState2);Serial.println("");delay(100);
  
  // if (buttonState1 == LOW){
  //   // digitalWrite(LED_PIN, HIGH);
  //   servo.write(0);delay(200); // Wait for 1 second
  //   handleJpgLo(); // Upload image with cam-lo.jpg endpoint
  //   Serial.println("buttonState1: ");Serial.println(buttonState1);delay(100);
  // }

  if (buttonState2 == HIGH){
    // digitalWrite(LED_PIN, HIGH);
    // servo.write(180);delay(200); // Wait for 1 second
    handleJpgLo(); // Upload image with cam-lo.jpg endpoint
    Serial.println("Uploading: ");Serial.println(buttonState2);delay(500);
  }

  // else {
  //   digitalWrite(LED_PIN, LOW);
  //   servo.write(90);delay(250);
  // }
  // delay(1000);

  // server.handleClient();
}
