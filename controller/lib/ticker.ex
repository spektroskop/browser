defmodule Ticker do
  use GenServer

  @interval 2_000

  def start_link(_) do
    GenServer.start_link(__MODULE__, 1, name: __MODULE__)
  end

  def init(_) do
    Process.send_after(self(), {:tick, 1}, @interval)
    {:ok, nil}
  end

  def handle_info({:tick, count}, _) do
    url = "http://localhost:8080/#{Integer.to_string(count)}"
    Controller.load_url(url)
    Process.send_after(self(), {:tick, count + 1}, @interval)
    {:noreply, nil}
  end
end
