import matplotlib.pyplot as plt
import numpy as np
import os

def load_data(filename):
    buckets = []
    counts  = []
    with open(filename, 'r') as f:
        for line in f:
            if ';' in line:
                bucket, count = map(int, line.strip().split(';'))
                buckets.append (bucket)
                counts. append (count)
    return buckets, counts

def plot_histogram(buckets, counts, filename):
    plt.figure  (figsize=(15, 6))
    
    # гистограмма распределения по ячейкам
    plt.subplot (1, 2, 1)
    plt.bar     (buckets, counts, width=1.0, alpha=0.7)
    plt.title   ('Распределение элементов по ячейкам')
    plt.xlabel  ('Номер ячейки')
    plt.ylabel  ('Количество элементов')
    plt.grid    (True, linestyle='--', alpha=0.5)
    plt.xlim    (0, 1500)  # 8000
    
    # гистограмма частот
    plt.subplot              (1, 2, 2)
    unique, freq = np.unique (counts, return_counts=True)
    plt.bar                  (unique, freq, width=0.8, alpha=0.7, color='orange')
    plt.title                ('Частота встречаемости размеров цепочек')
    plt.xlabel               ('Количество элементов в ячейке')
    plt.ylabel               ('Частота')
    plt.grid                 (True, linestyle='--', alpha=0.5)
    
    plt.tight_layout ()
    plt.savefig      (f'{filename}_histogram.png')
    plt.show         ()

if __name__ == '__main__':
    input_file = '/home/max/WORK/Hash_table/src/load_dump_8.txt' 
    
    if not os.path.exists(input_file):
        print (f"Файл {input_file} не найден!")
        print ("Текущая директория:", os.getcwd())
        exit  (1)
    
    buckets, counts = load_data(input_file)
    plot_histogram(buckets, counts, os.path.basename(input_file).split('.')[0])