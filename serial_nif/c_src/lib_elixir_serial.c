#include "erl_nif.h"

#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include "serial.h"

#define MAXBUFLEN 1024

static ERL_NIF_TERM _open(ErlNifEnv* env, int arc, const ERL_NIF_TERM argv[])
{
  char path[MAXBUFLEN];
  int fd;
  int int_speed = -1;

  enif_get_string(env, argv[0], path, 1024, ERL_NIF_LATIN1);
  enif_get_int(env, argv[1], &int_speed);

  fd = serial_open(path);
  serial_speed(fd, int_speed);

  return enif_make_int(env, fd);
}


static ERL_NIF_TERM _read(ErlNifEnv* env, int arc, const ERL_NIF_TERM argv[])
{
  int fd=-1;
  char buf[1];
  ErlNifBinary r;
  int res;

  enif_get_int(env, argv[0], &fd);
  res =read(fd,buf,1);

  if (res > 0)
  {
    enif_alloc_binary(1, &r);
    strcpy(r.data, buf);
    return enif_make_binary(env, &r);
  }

  enif_alloc_binary(0, &r);
  return enif_make_binary(env, &r);
}

static ERL_NIF_TERM _write(ErlNifEnv* env, int arc, const ERL_NIF_TERM argv[])
{
  char str[MAXBUFLEN];
  int fd, size;

  enif_get_int(env, argv[0], &fd);
  size = enif_get_string(env, argv[1], str, 1024, ERL_NIF_LATIN1);

  serial_write(fd, str, size-1);

  return enif_make_int(env, size);
}


static ERL_NIF_TERM _close(ErlNifEnv* env, int arc, const ERL_NIF_TERM argv[])
{
  int fd=-1;

  enif_get_int(env, argv[0], &fd);
  close(fd);
  return enif_make_int(env, fd);
}

static ErlNifFunc nif_funcs[] =
{
  {"_open", 2, _open},
  {"_read", 1, _read},
  {"_write", 2, _write},
  {"_close", 1, _close}
};

ERL_NIF_INIT(Elixir.Serial,nif_funcs,NULL,NULL,NULL,NULL)
