#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "erl_comm.h"
#include "serial.h"

int bytes_read;
int serial_bytes_read;
int serial_fd = 0;
char serial_buf[5];

void reset_state() {
  bytes_read = 0;
  serial_bytes_read = 0;
  strcpy(serial_buf, "");
}


void process_command(byte *buf, int bytes_read) {
  int fn = buf[0];

  if(bytes_read > 0) {
    if (fn == 1) {
      char device_name[1024];
      get_str_arg(buf, device_name, bytes_read);
      serial_fd = serial_open(device_name);
    }
    else if(fn == 2) {
      serial_speed(serial_fd, get_int_arg(buf, bytes_read));
    }
    else if(fn == 3) {
      char str[1024];
      get_str_arg(buf, str, bytes_read);

      serial_write(serial_fd, str, bytes_read-1);
    }
    else {
      fprintf(stderr, "not a valid fn %i\n", fn);
    }
  }
  else if(bytes_read < 0) {
    exit(1);
  }
}

void poll_serial_data(int serial_fd) {
  serial_bytes_read = read(serial_fd, serial_buf, 5);

  if(serial_bytes_read > 0) {
    write_cmd( (byte*) serial_buf, 5);
  }
}



int main() {
  byte buf[100];

  while (1) {
    reset_state();

    if(input_available() > 0 ) {
      bytes_read = read_cmd(buf);
      process_command(buf, bytes_read);
    }

    if(serial_fd > 0) {
      poll_serial_data(serial_fd);
    }
  }
}

