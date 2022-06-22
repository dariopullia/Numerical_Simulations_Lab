import tensorflow as tf
from tensorflow import keras

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation
from tensorflow.keras import backend as K
from tensorflow.keras.utils import get_custom_objects
import numpy as np
import matplotlib.pyplot as plt

NN= PLACEHOLDERNN #Number of Neurons
NL= PLACEHOLDERNL #Number of Layers
ActFun= 'PLACEHOLDERAFUN' #ACTIVATION FUNCTION
LFun = 'PLACEHOLDERLFUN'
Opt = 'PLACEHOLDEROPT'


# generate training inputs
np.random.seed(0)
x_train = np.random.uniform(-1, 1, 1000)
x_valid = np.random.uniform(-1, 1, 100)
x_valid.sort()
y_target = 4-3*x_valid-2*x_valid**2+3*x_valid**3 # ideal (target) polinomial function

sigma = 0.5 # noise standard deviation
y_train = np.random.normal(4-3*x_train-2*x_train**2+3*x_train**3, sigma) # actual measures from which we want to guess regression parameters
y_valid = np.random.normal(4-3*x_valid-2*x_valid**2+3*x_valid**3, sigma)

# compose the NN model
model = tf.keras.Sequential()
model.add(Dense(NN, input_shape=(1,), activation=ActFun))

for i in range(NL-1):
    model.add(Dense(NN,activation=ActFun))

model.add(Dense(1,activation='linear'))


# compile the model choosing optimizer, loss and metrics objects
model.compile(optimizer=Opt, loss=LFun, metrics=[LFun])

# get a summary of our composed model
#model.summary()
# fit the model using training dataset
# over 10 epochs of 32 batch size each
# report training progress against validation data
history = model.fit(x=x_train, y=y_train, 
          batch_size=100, epochs=30,
          shuffle=True, # a good idea is to shuffle input before at each epoch
          validation_data=(x_valid, y_valid))


# return weights and biases
model.get_weights()

save_model_path='models/model_NN%d_NL%d_AFun_%s_LFun_%s_Opt_%s.h5'%(NN,NL, ActFun,LFun,Opt)
model.save(filepath=save_model_path, include_optimizer=True)
