from time import pthread_getcpuclockid
from turtle import shape
from wsgiref.util import shift_path_info
import matplotlib
import matplotlib.pyplot as plt
from requests import PreparedRequest
import numpy as np
from scipy.optimize import curve_fit
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.collections import LineCollection
import imageio
import sys


if len(sys.argv)!=3:
    print("Numero errato input")
    print("0 Circ, 1 Square")
    print("0 PreCross, 1 Post")
    quit()

Shape = int(sys.argv[1])

PrePost= int(sys.argv[2])

print(Shape)
print(PrePost)
C=0




if (not Shape and not PrePost):
    print("CICLO PRECROSS CIRC")

    X,Y = np.loadtxt("data01/PreCrossover/Circ/Region.dat",  usecols=(0,1), delimiter=' ', unpack='true')
    Best = np.loadtxt("data01/PreCrossover/Circ/Bests.dat",)
    fig=plt.figure(figsize=(5, 5))
    filenames=[]
    N=(X.size)
    for j in range(0,len(Best)):
        Xord=[]
        Yord=[]
        fig=plt.figure(figsize=(8, 8))


        for i in range(X.size):
            Xord.append(X[int(Best[j][i])])
            Yord.append(Y[int(Best[j][i])])


        plt.plot(Xord,Yord,marker="o",markersize=4,lw=1.3, label="Gen"+str(j)+"    Len: "+str(Best[j][N]))  
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.ylim([-1.5, 1.5])
        plt.xlim([-1.5, 1.5])
        plt.grid(True)
        plt.legend()
        plt.savefig("data01/PreCrossover/figsCirc/%s.png"%j,format="png", dpi=150)
        filenames.append("data01/PreCrossover/figsCirc/%s.png"%j)
        plt.close(fig)


    with imageio.get_writer('data01/PreCrossover/figsCirc/movie.gif', mode='I') as writer:
        for filename in filenames:
            image = imageio.imread(filename)
            writer.append_data(image)

    print("FINE CICLO PRECROSS CIRC")
   




if (Shape and not PrePost):
    print("CICLO PRECROSS SQUARE")   
    X,Y = np.loadtxt("data01/PreCrossover/Square/Region.dat",  usecols=(0,1), delimiter=' ', unpack='true')
    Best = np.loadtxt("data01/PreCrossover/Square/Bests.dat",)
    fig=plt.figure(figsize=(5, 5))
    filenames=[]
    N=(X.size)
    for j in range(0,len(Best)):
        Xord=[]
        Yord=[]
        fig=plt.figure(figsize=(8, 8))


        for i in range(X.size):
            Xord.append(X[int(Best[j][i])])
            Yord.append(Y[int(Best[j][i])])

        plt.plot(Xord,Yord,marker="o",markersize=4,lw=1.3, label="Gen"+str(j)+"    Len: "+str(Best[j][N]))  
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.ylim([-1.5, 1.5])
        plt.xlim([-1.5, 1.5])
        plt.grid(True)
        plt.legend()
        plt.savefig("data01/PreCrossover/figsSquare/%s.png"%j,format="png", dpi=150)
        filenames.append("data01/PreCrossover/figsSquare/%s.png"%j)
        plt.close(fig)
        

    with imageio.get_writer('data01/PreCrossover/figsSquare/movie.gif', mode='I') as writer:
        for filename in filenames:
            image = imageio.imread(filename)
            writer.append_data(image)
    
    print("FINE CICLO PRECROSS SQUARE")





if (not Shape and PrePost):
    print("CICLO CIRC")
    X,Y = np.loadtxt("data01/Circ/Region.dat",  usecols=(0,1), delimiter=' ', unpack='true')
    Best = np.loadtxt("data01/Circ/Bests.dat",)
    fig=plt.figure(figsize=(5, 5))
    filenames=[]
    N=(X.size)
    L=len(Best)
    print(L)
    for j in range(0,L): 
        if j%4!=0 or j>400:
            continue
        print(j)
        Xord=[]
        Yord=[]
        fig=plt.figure(figsize=(8, 8))


        for i in range(X.size):
            Xord.append(X[int(Best[j][i])])
            Yord.append(Y[int(Best[j][i])])


        plt.plot(Xord,Yord,marker="o",markersize=4,lw=1.3, label="Gen"+str(j)+"    Len: "+str(Best[j][N]))  
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.ylim([-1.5, 1.5])
        plt.xlim([-1.5, 1.5])
        plt.grid(True)
        plt.legend()
        plt.savefig("data01/figsCirc/%s.png"%j,format="png", dpi=150)
        filenames.append("data01/figsCirc/%s.png"%j)
        plt.close(fig)

    with imageio.get_writer('data01/figsCirc/movie.gif', mode='I') as writer:
        for filename in filenames:
            image = imageio.imread(filename)
            writer.append_data(image)

    print("FINE CICLO CIRC")





if (Shape and PrePost):
    print("CICLO SQUARE")
    X,Y = np.loadtxt("data01/Square/Region.dat",  usecols=(0,1), delimiter=' ', unpack='true')
    Best = np.loadtxt("data01/Square/Bests.dat",)
    fig=plt.figure(figsize=(5, 5))
    filenames=[]
    N=(X.size)
    for j in range(0,len(Best)):
        if j%4!=0 or j>600:
            continue


        Xord=[]
        Yord=[]
        fig=plt.figure(figsize=(8, 8))


        for i in range(X.size):
            Xord.append(X[int(Best[j][i])])
            Yord.append(Y[int(Best[j][i])])


        plt.plot(Xord,Yord,marker="o",markersize=4,lw=1.3, label="Gen"+str(j)+"    Len: "+str(Best[j][N]))  
        plt.xlabel('X')
        plt.ylabel('Y')
        plt.ylim([-1.5, 1.5])
        plt.xlim([-1.5, 1.5])
        plt.grid(True)
        plt.legend()
        plt.savefig("data01/figsSquare/%s.png"%j,format="png", dpi=150)
        filenames.append("data01/figsSquare/%s.png"%j)
        plt.close(fig)

    with imageio.get_writer('data01/figsSquare/movie.gif', mode='I') as writer:
        for filename in filenames:
            image = imageio.imread(filename)
            writer.append_data(image)        

    print("FINE CICLO SQUARE")


print("FINE DI TUTTO")