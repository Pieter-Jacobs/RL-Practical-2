import matplotlib.pyplot as plt
import csv

x0=[]
y0=[]

with open('sarsaEpsilon.txt', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x0.append(int(row[0]))
        y0.append(int(row[1]))

plt.plot(x0,y0, marker='o')

x1=[]
y1=[]

with open('qLearningEpsilon.txt', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x1.append(int(row[0]))
        y1.append(int(row[1]))

plt.plot(x1,y1, marker='o')

plt.title('Q-Learning vs Sarsa: Epsilon-Greedy')

plt.xlabel('Episodes')
plt.ylabel('Average amount of steps')

plt.show()
