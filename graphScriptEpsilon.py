import matplotlib.pyplot as plt
import csv

x0=[]
y0=[]

with open('sarsaEpsilon.csv', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x0.append(float(row[0]))
        y0.append(float(row[1]))

plt.plot(x0,y0, marker='o')
plt.ticklabel_format(useOffset=False, style='plain')

x1=[]
y1=[]

with open('qLearningEpsilon.csv', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x1.append(float(row[0]))
        y1.append(float(row[1]))

plt.plot(x1,y1, marker='o')
plt.ticklabel_format(useOffset=False, style='plain')
plt.legend(['Sarsa', 'Q-Learning'])

plt.title('Q-Learning vs Sarsa: Epsilon-Greedy')

plt.xlabel('Episodes')
plt.ylabel('Average amount of steps')

plt.show()
