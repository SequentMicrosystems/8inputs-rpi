import lib8inputs as i

print("============================")
print("read all inputs = " + str(i.get_opto_all(0)))
print("============================")
for i in range(8):
    opt = r.get_opto(0, i+1)
    print("input " + str(i+1) + " status = " + str(opt))
