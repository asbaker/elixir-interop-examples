defmodule Serial do
  @on_load :init

  def init() do
    :erlang.load_nif("./priv_dir/lib_elixir_serial", 0)
    :ok
  end

  def open(device, speed) do
    _open(String.to_char_list(device), speed)
  end

  def read(fd) do
    _read(fd)
  end

  def write(fd, str) do
    _write(fd, String.to_char_list(str))
  end

  def close(fd) do
    _close(fd)
  end

  def _open(device, speed) do
    "NIF library not loaded"
  end

  def _read(fd) do
    "NIF library not loaded"
  end

  def _close(fd) do
    "NIF library not loaded"
  end

  def _write(fd, str) do
    "NIF library not loaded"
  end
end

