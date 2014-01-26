--[[
   [
   [ Author: KK <thumbd03803@gmail.com>
   [ 
   [ drawSomething.lua
   [
   ]]

for i = 0, 5 do
	for j = 0, 5 do
		Draw( "sphere", i*5, j*5, 0 )
	end
end

for i = 0, 5 do
	for j = 0, 5 do
		Draw( "stick", i*5, j*5, 5 )
	end
end

for i = 0, 5 do
	for j = 0, 5 do
		Draw( "cube", i*5, j*5, 10 )
	end
end

for i = 0, 5 do
	for j = 0, 5 do
		Draw( "monkey", i*5, j*5, 20 )
	end
end
