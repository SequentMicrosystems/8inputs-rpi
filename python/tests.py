import lib8inputs as i

print("============================")
print("read all inputs = " + str(i.get_opto_all(0)))
print("============================")
for j in range(8): 
    opt = i.get_opto(0, j+1) 
    print("input " + str(j+1) + " status = " + str(opt))
