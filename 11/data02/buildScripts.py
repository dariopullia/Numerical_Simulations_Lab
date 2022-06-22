#NN=[1,5,10,20,30,40,50,60,70,80,90]
#NL=[1,5,10,15,20,25]

NN=[50]
NL=[10]

AFun=['relu']

LFun=['mean_squared_error','mean_squared_logarithmic_error','logcosh',]
Opt=['SGD','Adagrad','Adadelta']

for i in NN:
    for j in NL:
        for k in AFun:
            for m in LFun:
                for n in Opt:
                    out=open('NN%d_NL%d_AFun_%s_LFun_%s_Opt_%s.py'%(i,j,k,m,n),'w')
                    temp=open('template.py','r')
                    tempstring=temp.read()
                    temp.close()
                    tempstring=tempstring.replace('PLACEHOLDERNN',str(i))
                    tempstring=tempstring.replace('PLACEHOLDERNL',str(j))
                    tempstring=tempstring.replace('PLACEHOLDERAFUN',k)
                    tempstring=tempstring.replace('PLACEHOLDERLFUN',m)
                    tempstring=tempstring.replace('PLACEHOLDEROPT',n)
                    out.write(tempstring)
