defmodule Controller do
  require Logger
  use GenServer

  def start_link(_) do
    GenServer.start_link(__MODULE__, nil, name: __MODULE__)
  end

  def load_url(url) do
    GenServer.cast(__MODULE__, {:load_url, url})
  end

  def init(_) do
    cmd = "../browser/browser.app/Contents/MacOS/browser"

    port =
      Port.open(
        {:spawn_executable, cmd},
        [:binary, {:args, ["http://localhost:8080/default"]}]
      )

    {:ok, port}
  end

  def handle_cast({:load_url, url}, port) do
    Port.command(port, "#{url}\n")
    {:noreply, port}
  end
end
