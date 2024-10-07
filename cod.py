a=2
b=3
c=1
for i in range(11):
    print("%d x %d = %d" % (a,i,a*i))
    print("%d x %d = %d" % (b,i,b*i))
    print("%d x %d = %d" % (a,b,a*b))
    c= c+i
print(c)