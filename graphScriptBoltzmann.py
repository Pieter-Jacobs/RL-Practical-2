import matplotlib.pyplot as plt
import csv

x0=[]
y0=[]

with open('sarsaBoltzmann.csv', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x0.append(float(row[0]))
        y0.append(float(row[1]))

plt.plot(x0,y0, marker='o')
plt.legend(['Sarsa'])

x1=[]
y1=[]

with open('qLearningBoltzmann.csv', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x1.append(float(row[0]))
        y1.append(float(row[1]))

plt.plot(x1,y1, marker='o')
plt.legend(['Sarsa', 'Q-Learning'])

plt.title('Q-Learning vs Sarsa: Boltzmann Exploration 50x50')

plt.xlabel('Episodes')
plt.ylabel('Average amount of steps')

plt.show()
