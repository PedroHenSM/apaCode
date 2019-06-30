import pandas as pd
import numpy as np
from scipy import stats
#import scikit_posthocs as sp
#import matplotlib.pyplot as plt
import os

folder = 'data_results/'
ids = os.listdir(folder)
ids = np.sort(np.array([x for x in ids if '.txt' in x]))

if not os.path.exists('stats_analysis/'):
        os.makedirs('stats_analysis/')

## RESUME
if not os.path.exists('stats_analysis/resume/'):
        os.makedirs('stats_analysis/resume/')
        
for c_ids in range(len(ids)):
    T = pd.read_csv(folder+ids[c_ids], sep='\t')
    H = T.columns.values
    T = np.array(T).T
    F = []
    for i in range(len(H)):
        F.append([np.mean(T[i]), np.std(T[i]), np.median(T[i]), np.min(T[i]), np.max(T[i])])
    F = pd.DataFrame(F, index=H)
    F.to_csv('stats_analysis/resume/resume_'+ids[c_ids], sep='\t', header=['mean', 'std', 'median', 'min', 'max'], float_format='%.6f')


## P_VALUE
'''
if not os.path.exists('stats_analysis/p_value/'):
        os.makedirs('stats_analysis/p_value/')

kruskal_values = []
for c_ids in range(len(ids)):
    T = pd.read_csv(folder+ids[c_ids], sep='\t')
    H = T.columns.values
    T = np.array(T).T
    dunn_test = sp.posthoc_dunn(T)
    kruskal_values.append(stats.kruskal(*T)[1])
    for i in range(len(H)):
        dunn_test[i][i] = 1
    dunn_test = pd.DataFrame(dunn_test, index=H)
    dunn_test.to_csv('stats_analysis/p_value/dunn_test_'+ids[c_ids], sep='\t', header=H, float_format='%.6f')
    
kruskal_values = pd.DataFrame(np.array(kruskal_values).T, index=ids)
kruskal_values.to_csv('stats_analysis/p_value/kruskal.txt', sep='\t', header=['p_value'], float_format='%.6f')
'''
## BOXPLOT
'''
if not os.path.exists('stats_analysis/boxplot/'):
        os.makedirs('stats_analysis/boxplot/')

def significance(T, P):
    amplitude = np.max(T)-np.min(T)
    base = 0
    add = 0.07*amplitude
    for i in range(len(P)):
        for j in range(i+1, len(P)):
            if P[i, j] <= 0.05:
                base = base+add
                #plt.plot([i+1, i+1, j+1, j+1], [np.max(T.T[i])+add, np.max(T)+add+base, np.max(T)+add+base, np.max(T.T[j])+add], color='black')
                plt.plot([i+1, j+1], [np.max(T)+add+base, np.max(T)+add+base], color='black')
                plt.plot([i+1, j+1], [np.max(T)+add+base, np.max(T)+add+base], color='black')
                if P[i, j] >= 0.001:
                    plt.text(i+1.03, np.max(T)+1.5*add+base, r'$p=%.3f$'%P[i, j], horizontalalignment='left', verticalalignment='center', color='black', fontsize='19')
                else:
                    plt.text(i+1.03, np.max(T)+1.5*add+base, r'$p < 0.001$', horizontalalignment='left', verticalalignment='center', color='black', fontsize='19')

for c_ids in range(len(ids)):
    T = pd.read_csv(folder+ids[c_ids], sep='\t')
    H = T.columns.values
    T = np.array(T)
    plt.figure()
    plt.subplots(figsize=[10, 10])
    plt.xticks(fontsize='20')
    plt.yticks(fontsize='20')
    plt.subplots_adjust(left=0.10, right=0.99, top=0.99, bottom=0.04)
    plt.boxplot(T, labels=H)
    P = np.array(pd.read_csv('stats_analysis/p_value/dunn_test_'+ids[c_ids], sep='\t'))[:,1:]
    significance(T, P)
    plt.savefig('stats_analysis/boxplot/boxplot_'+ids[c_ids][:-4]+'.eps', format='eps', dpi=500, transparent = True)
    #plt.savefig('stats_analysis/boxplot/boxplot_'+ids[c_ids][:-4]+'.jpg', format='jpg', dpi=500)
    plt.close('all')
'''
## PERFORMANCE_PROFILE
if len(ids) > 1:
    if not os.path.exists('stats_analysis/performance_profile/'):
            os.makedirs('stats_analysis/performance_profile/')

    F = []
    for c_ids in range(len(ids)):
        F.append([])
        T = pd.read_csv(folder+ids[c_ids], sep='\t')
        H = T.columns.values
        T = np.array(T).T
        for i in range(len(H)):
            F[-1].append(np.mean(T[i]))

    F = np.array(F)

    F = 1/F # invertion

    for i in range(len(F)): # normalize
        F[i] = F[i]/np.min(F[i])

    F = np.sort(F.T)

    plt.figure()
    plt.subplots(figsize=[10, 10])
    plt.subplots_adjust(left=0.10, right=0.99, top=0.99, bottom=0.08)
    #plt.subplots_adjust(left=0.01, right=0.99, top=0.99, bottom=0.08)
    #plt.xlim(0.95, 1.45)
    #plt.xlim(1.45, 8.05)
    #plt.xscale('log')
    #plt.minorticks_off()
    #plt.xticks([2, 3, 4, 6], ['2','3','4','6'])
    plt.xticks(fontsize='19')
    plt.yticks(fontsize='19')

    R = []
    for c_F in range(len(F)):
        R.append([])
        R[-1].append(F[c_F].tolist().count(1))
        R[-1].append(np.max(F[c_F]))
        X = [1]
        Y = [0]
        ss = 0
        for i in range(len(F[c_F])):
            if X[-1] == F[c_F,i]:
                X.append(X[-1])
                Y.append(Y[-1]+1/len(F[0]))
            else:
                ss = ss + ((F[c_F,i]-X[-1])*Y[-1])
                X.append(F[c_F,i])
                Y.append(Y[-1])
                X.append(F[c_F,i])
                Y.append(Y[-1]+1/len(F[0]))
        X.append(np.max(F)+0.05*(np.max(F)-1))
        Y.append(1)
        ss = ss + (X[-1]-X[-2])
        R[-1].append(ss)
        plt.plot(X,Y)
    R = pd.DataFrame(R, index=H)
    R.to_csv('stats_analysis/performance_profile/performance_profile.txt', sep='\t', header=['best_in', 'worst', 'integrate'], float_format='%.6f')

    plt.xlabel(r"$\tau$", fontsize='20')
    plt.ylabel(r"$\rho\ (\tau)$", fontsize='20')
    plt.legend(H, loc="lower right", fontsize='19')
    plt.savefig('stats_analysis/performance_profile/performance_profile.eps', format='eps', dpi=500, transparent = True)
    #plt.savefig('stats_analysis/performance_profile/performance_profile.jpg', format='jpg', dpi=500)
    plt.close('all')

