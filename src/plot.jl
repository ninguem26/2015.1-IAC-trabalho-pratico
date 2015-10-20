#The graph is generated by the Python library PyPlot
using PyPlot

memoria = [] #Memory values
cpu = [] #CPU values
i = 1

plotFile = open("plot.txt") #Opening plot.txt file to read the data
lines = readlines(plotFile) #Each line of the file becomes an array element

for item in lines
    column = split(item, " ")
    push!(memoria, parse(Int, column[3])) #Adding memory values
    push!(cpu, parse(Float64, column[2])) #Adding CPU values
    i = i+1
end
close(plotFile) #Closing file

#Plotting data with two subplots

subplot(211) #Memory over Time subplot
plot(memoria, "b-")
ylabel("Consumo Memória (KB)", color="b")
grid()

subplot(212) #CPU over Time subplot
plot(cpu, "g-")
ylabel("Consumo CPU (%)", color="g")
grid()

xlabel("Tempo (s)")
savefig("plots/"*Libc.strftime(Dates.time())) #Save the image plotted with the date and time as name
show()