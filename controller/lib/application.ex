defmodule Controller.Application do
  use Application

  @impl true
  def start(_, _) do
    Supervisor.start_link(
      [Controller, Ticker],
      strategy: :one_for_one,
      name: Controller.Supervisor
    )
  end
end
