#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd

# df = pd.read_csv("test.csv", index_col=0)
df = pd.read_csv("outputFinal.csv", index_col=0)
df = df.groupby("instancia").mean().reset_index()
otimos = pd.read_csv("otimos.txt", sep="=")
otimos = otimos.reset_index()
otimos['index'] = otimos['index'].map(lambda x: x.strip()+'.txt')
df = df.merge(otimos, how='left', left_on='instancia', right_on='index')
df[' otimo'] = df['Solucoes otimas']
df[' gap_guloso'] = ((df[' solucao_gulosa'] - df[' otimo']) / df[' otimo']) * 100
df[' gap_vnd'] = ((df[' solucao_vnd'] - df[' otimo']) / df[' otimo']) * 100
df[' gap_ils'] = ((df[' solucao_ils'] - df[' otimo']) / df[' otimo']) * 100
df.drop(["index", "Solucoes otimas"], axis=1)

