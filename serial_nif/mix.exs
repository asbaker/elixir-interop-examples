defmodule SerialNif.Mixfile do
  use Mix.Project

  def project do
    [app: :serial_nif,
     version: "0.0.1",
     elixir: "~> 1.0",
     compilers: [:make, :elixir, :app], # Add the make compiler
     aliases: aliases, # Configure aliases
     deps: deps]
  end

  defp aliases do
    # Execute the usual mix clean and our Makefile clean task
    [clean: ["clean", "clean.make"]]
  end

  def application do
    [applications: [:logger]]
  end

  defp deps do
    []
  end
end

###################
# Make file Tasks #
###################

defmodule Mix.Tasks.Compile.Make do
  @shortdoc "Compiles helper in c_src"

  def run(_) do
    {result, _error_code} = System.cmd("make", [], stderr_to_stdout: true)
    Mix.shell.info result

    :ok
  end
end

defmodule Mix.Tasks.Clean.Make do
  @shortdoc "Cleans helper in c_src"

  def run(_) do
    {result, _error_code} = System.cmd("make", ['clean'], stderr_to_stdout: true)
    Mix.shell.info result

    :ok
  end
end

