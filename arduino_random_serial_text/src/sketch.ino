#define ARRAY_SIZE 4

static String data[ARRAY_SIZE] = {
  "This is some data.",
  "42",
  "{watch_out: \"For JSON\"}",
  "Woohoo we got more some!"
};

int i;

void setup() {
  Serial.begin(115200);
}

void loop() {
  i = random(0,ARRAY_SIZE);

  Serial.println(data[i]);
  delay(2000);
}
