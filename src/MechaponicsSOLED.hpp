Adafruit_SSD1306 OLED_DISPLAY(OLED_WIDTH, OLED_HIGH, &Wire, OLED_RESET);

void writeOLED(int xCursor, int yCursor, int textSize, String messageOLED)
{
  OLED_DISPLAY.setFont(&FreeSerif9pt7b);
  OLED_DISPLAY.setCursor(xCursor, yCursor);
  OLED_DISPLAY.setTextSize(textSize);
  OLED_DISPLAY.print(messageOLED);
  OLED_DISPLAY.display();
}

void showParametersOLED()
{
  OLED_DISPLAY.clearDisplay();
  writeOLED(0, 13, 1, "SN pH Dn: "+ String(cProfileSN.valpHDown));
  writeOLED(10, 28, 0, "MS-Node 1");
  delay(2000);
  OLED_DISPLAY.clearDisplay();
  writeOLED(0, 13, 1, "SN pH Up: "+ String(cProfileSN.valpHUp));
  writeOLED(10, 28, 0, "MS-Node 1");
  delay(2000);
  OLED_DISPLAY.clearDisplay();
  writeOLED(0, 13, 1, "SN EC Dn: "+ String(cProfileSN.valECDown));
  writeOLED(10, 28, 0, "MS-Node 1");
  delay(2000);
  OLED_DISPLAY.clearDisplay();
  writeOLED(0, 13, 1, "SN EC Up: "+ String(cProfileSN.valECUp));
  writeOLED(10, 28, 0, "MS-Node 1");
  delay(2000);
}

void initOLED()
{
  Wire.begin();
  OLED_DISPLAY.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  OLED_DISPLAY.clearDisplay();
  OLED_DISPLAY.setTextColor(WHITE);
  OLED_DISPLAY.clearDisplay();
  OLED_DISPLAY.display();
  writeOLED(0, 13, 1, "Mechaponics");
  writeOLED(10, 28, 0, "System");
}