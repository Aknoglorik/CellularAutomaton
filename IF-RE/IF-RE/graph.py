import matplotlib.pyplot as plt

XX = []
YY = []


with open("graph.txt", 'r') as file:
    str = file.read()

def __int(str):
    if (str): 
        return int(str)
    return 0

vals = list(map(__int, (str.split(' '))))

for i in range(0, len(vals)-1, 2):
    XX.append(vals[i])
    YY.append(vals[i+1])

plt.xlabel("Номер поколения");
plt.ylabel("Количество шагов");
plt.title("Зависимость шагов от номера поколения")
plt.plot(XX, YY)
plt.show()