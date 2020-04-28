import matplotlib.pyplot as plt
import csv

with open("Results.csv") as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    counter=0
    points_1=[]
    points_2 = []
    points_3 = []
    counter_list=[]
    for row in csv_reader:
        print(row[0] , row[1] ,row[2])
        counter += 1
        points_1.append(float(row[0]))
        points_2.append(float(row[1]))
        points_3.append(float(row[2]))
        counter_list.append((counter))
    plt.plot(counter_list, points_1, color='red', label='Grade_School_Multiplication')
    plt.plot(counter_list, points_2, color='blue', label='Divide_and_Conquer_Algorithm')
    plt.plot(counter_list, points_3, color='green', label='Karatsuba_Multiplication')
    plt.show()
    csv_file.close()