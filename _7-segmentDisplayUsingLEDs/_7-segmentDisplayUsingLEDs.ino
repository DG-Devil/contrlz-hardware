//assigined a Arduino pin for each segment
const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};

// Digit definitions for common cathode 7-segment display
// Each sub-array corresponds to the segments a, b, c, d, e, f, g and their corresponding behavior
// A value of HIGH will light the LED and LOW will turn the LED off
const int digits[10][7] = {
  // the order of this is segmet wise {a, b, c, d, e, f, g}
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},// 0
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},// 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},// 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},// 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},// 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},// 5
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},// 6
  {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},// 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},// 8
  {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH}// 9
};

void setup() {
  // Initializing each segment pin as an OUTPUT.
  for (int i = 0; i < 7; i++){
    pinMode(segmentPins[i], OUTPUT);
  }
  
  // Initializing Serial communication at 9600 baud.
  Serial.begin(9600);
  Serial.println("Enter a digit (0-9) and press enter:");
}

void loop() {
  // Checking if there is Serial input.
  if (Serial.available() > 0) {
    // Reading the incoming byte as a character and converting it to a integer.
    int digit = Serial.read() - '0';
    
    // Validating weather the input is a digit between 0 and 9 or not
    if (digit >= 0 && digit <= 9) {
      displayDigit(digit);
      Serial.print("Displaying: ");
      Serial.println(digit);
    } else {
      Serial.println("Please enter a digit between 0 and 9.");
    }
  }
}

// Function to update the LED segments based on the digit provided.
void displayDigit(int digit) {
  for (int i = 0; i < 7; i++){
    digitalWrite(segmentPins[i], digits[digit][i]); // each pin is set to HIGH or LOW based on the previously set values for each digit
    // goes to the digits array and goes to the row corresponding to the digit entered
    // then in that row all the pins behavior is pre defined
    // now just iterating on that row and setting all the pins to their respective expected behaviour
  }
}
