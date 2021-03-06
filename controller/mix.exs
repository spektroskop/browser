defmodule Controller.MixProject do
  use Mix.Project

  def project do
    [
      app: :controller,
      version: "0.1.0",
      elixir: "~> 1.13",
      start_permanent: Mix.env() == :prod,
      deps: deps()
    ]
  end

  def application do
    [
      extra_applications: [:logger],
      mod: {Controller.Application, []}
    ]
  end

  defp deps do
    []
  end
end
