#!/usr/bin/env lua

--[[
	Simulation parameter specification is performed in Lua. This demonstration
	code is effectively nothing more thatn a "Hello, World!" application.
--]]

-- Create the photometer job
job = nix.photometer_job()

-- verbose output
job:set_verbose(true)

-- Declare some wavelengths to investigate
start_lambda	= 350
end_lambda		= 2500
step			= 10
wavelengths = {}
for lambda = start_lambda, end_lambda, step do
	table.insert(wavelengths, lambda)
end
job:set_wavelengths(wavelengths)

job:run()

return true

