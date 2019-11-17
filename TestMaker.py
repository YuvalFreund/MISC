import random
f = open("guru100.txt","w+")
f.write("EXP ")
for i in range(100):
	j = random.randint(1,4);
	if j % 4 == 0:
		f.write("+ ")
	if j % 4 == 1:
		f.write("- ")
	if j % 4 == 2:
		f.write("* ")
	if j % 4 == 3:
		f.write("/ ")
for i in range(101):
	f.write(str(random.randint(1,50))+" ")


