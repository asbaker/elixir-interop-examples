defmodule Serial do
  def init() do
    Process.flag(:trap_exit, true)
    port = Port.open({:spawn, "priv_dir/serial"}, [{:packet, 2}])
  end

  def open(p, device, speed) do
    Port.command(p, [1,device])
    Port.command(p, [2,"#{speed}"])
  end

  def write(p, str) do
    Port.command(p, [3, str]);
  end
end


defmodule A do
  def a() do
    port = Serial.init()
    Port.list()
    IO.puts Serial.open(port, "/dev/tty.usbmodem1411", 115200)
    Port.list()

    :timer.sleep(3000) # wait for arduino sketch to wake

    Serial.write(port, "Testing!!")
    port
  end

  def rl() do
    receive do
      {_, {:data, data}} ->
        IO.puts "received #{data}"
    end

    rl()
  end
end
