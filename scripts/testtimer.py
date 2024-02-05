import time

start_data = time.time()

x = 0

while (x<1000000) : 
    x=x+1
    print(x)

end_data = time.time()
data = end_data - start_data
print(data)
