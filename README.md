# page_replacement
> page replacement algorithm simulator

<br/>

### program start:
```
make
```  
```
./simulator.out
```  

<br/>

### simulation:
```
Select page replacement algorithm simulator (maximum 3 but (8) can only be selected by itself)
(1) OPTIMAL  (2) FIFO  (3) LIFO  (4) LRU  (5) LFU  (6) SC  (7) ESC  (8) ALL
```  
```
Enter number of page frame (3~10)
```  
```
Select how to input data
(1) Randomly  (2) File
```   
- if you choose (1) Randomly, ```Enter number of string size``` <br/>
- if you choose (2) File, ```Enter file name```
```
Do you want to save the output to output.txt? (Y/N)
```  
=== simulation result ===
```
Do you want to be continue the simulator? (Y/N)
```  

<br/>

### simulation result:
```
=== OOO simulation start ===

#1     page: 17   frame: 17  0  0  0  0   F   
...  
#500   page: 19   frame: 19 22  7 16 15   F

=== OOO simulation end ===
```

<br/>

### algorithm description:
[page_replacement_algorithm](https://blog.naver.com/60cogml/222932944795)

<br/>

### report
[report](https://github.com/chaeheejo/page_replacement/blob/main/report.pdf)
