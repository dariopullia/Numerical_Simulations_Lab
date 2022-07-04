


'''
#NN=[1,5,10,20,30,40,50,60,70,80,90]
#NL=[1,5,10,15,20,25]
#NN=[1,5,10,20,30,40]
#NL=[1,5,10,15,20]

#AFun=['relu','sigmoid','tanh','softplus']
#NN=[50]
#NL=[10]

#AFun=['relu']

LFun=['mean_squared_error','mean_squared_logarithmic_error','logcosh',]
Opt=['SGD','Adagrad','Adadelta']

NN=[1,5,10,20,30,40,50,60,70,80,90]
NL=[1,5,10,15,20,25,30]
AFun=['relu']
LFun=['mean_squared_error',]
Opt=['SGD']
'''
NN=[50]
NL=[10]
AFun=['relu']

LFun=['mean_squared_error','mean_squared_logarithmic_error','logcosh',]
Opt=['SGD','Adagrad','Adadelta']


out3=open('Run3.sh','w')
out2=open('Run2.sh','w')
out1=open('Run1.sh','w')
for a,i in enumerate(NN):
    for b,j in enumerate(NL):
        for c,k in enumerate(AFun):
            for d,m in enumerate(LFun):
                for e,n in enumerate(Opt):
                    if ((a+b+c+d+e)%3==0): 
                        out1.write('python3 template.py %d %d %s %s %s \n'%(i,j,k,m,n))
                    if ((a+b+c+d+e)%3==1): 
                        out2.write('python3 template.py %d %d %s %s %s \n'%(i,j,k,m,n))
                    if ((a+b+c+d+e)%3==2): 
                        out3.write('python3 template.py %d %d %s %s %s \n'%(i,j,k,m,n))



