---@diagnostic disable: deprecated
return function(value)
	local power = math.floor(math.log10(value) + 1)
	local temp = value
	local sum = 0
	for _ = 1, power do
		local digit = temp % 10
		temp = math.floor((temp - digit) / 10)
		sum = sum + math.pow(digit, power)
	end

	return sum == value
end
