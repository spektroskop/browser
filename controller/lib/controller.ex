defmodule Controller do
  use GenServer

  @command Application.compile_env(:controller, :command)
  @default Application.compile_env(:controller, :default)

  def start_link(_) do
    GenServer.start_link(__MODULE__, nil, name: __MODULE__)
  end

  def load_url(url) do
    GenServer.cast(__MODULE__, {:load_url, url})
  end

  def init(_) do
    port =
      Port.open(
        {:spawn_executable, @command},
        [:binary, {:args, [@default]}]
      )

    {:ok, port}
  end

  def handle_cast({:load_url, url}, port) do
    Port.command(port, "#{url}\n")
    {:noreply, port}
  end
end
