import lib4relind as r

for i in range(4):
    r.set_relay(0, i+1, 1)
    print("set relay " + str(i+1) + " ON")
print("============================")
for i in range(4):
    rel = r.get_relay(0, i+1)
    print("relay " + str(i+1) + " status = " + str(rel))
print("============================")
r.set_relay_all(0,0)
print("Set all relays off")
print("read all relays = " + str(r.get_relay_all(0)))
print("============================")
r.set_relay_all(0,15)
print("Set all relays on")
print("read all relays = " + str(r.get_relay_all(0)))
print("============================")
for i in range(4):
    r.set_relay(0, i+1, 0)
    print("set relay " + str(i+1) + " OFF")
print("============================")
for i in range(4):
    rel = r.get_relay(0, i+1)
    print("relay " + str(i+1) + " status = " + str(rel))
print("============================")
print("read all inputs = " + str(r.get_opto_all(0)))
print("============================")
for i in range(4):
    opt = r.get_opto(0, i+1)
    print("input " + str(i+1) + " status = " + str(opt))