import numpy as np



def get_cartesian(lat=None,lon=None):
    lat, lon = np.deg2rad(lat), np.deg2rad(lon)
    R = 6371 # radius of the earth
    x = R * np.cos(lat) * np.cos(lon)
    y = R * np.cos(lat) * np.sin(lon)
    z = R *np.sin(lat)
    return x,y,z



lat,lon = np.loadtxt("Capoluoghi_coord.dat",  usecols=(0,1), delimiter='\t', unpack='true')


x,y,z=get_cartesian(lat, lon)


file = open('Capoluoghi.dat', 'w')

file2 = open('Capoluoghi_coord2.dat', 'w')


for i in range(len(x)):
    file.write("%f %f\n"%(x[i]-4000, y[i]-1000))
    file2.write("%f %f\n"%(lat[i], lon[i]))


file.close()