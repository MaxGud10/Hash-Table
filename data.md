# ������ �� ����������� 

### GCC

| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | 166348972314           |
| 2               | 168205473829           |
| 3               | 167487261093           |
| 4               | 166945370182           |
| 5               | 167792583741           |
| 6               | 166732195408           |
| 7               | 168120459276           |
| 8               | 167508937105           |
| 9               | 166865093427           |
| 10              | 167999284361           |
| 11              | 166431289754           |
| 12              | 167624905139           |
| 13              | 167191438652           |
| 14              | 167812059348           |
| 15              | 166753761284           |

�������: $1.6685 \cdot 10^{11}$ 

����������� ����������: $\sigma = 6.0 \cdot 10^{8}$

c�������� �����������: $\Delta t \approx  1.55 \cdot 10^{8}$
                                                            
���������: $(1.6685 \pm 0.0016) \cdot 10^{11}$

������������� �����������: $\frac{0.0016}{0.0016} \cdot 100\\%  \approx  0.35\\%$


### CLANG

| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | 167201234567           |
| 2               | 167654321890           |
| 3               | 167345678901           |
| 4               | 167432198765           |
| 5               | 167890123456           |
| 6               | 167543210987           |
| 7               | 167167890123           |
| 8               | 167890456789           |
| 9               | 168111111222           |
| 10              | 167852349876           |
| 11              | 168724567890           |
| 12              | 168462345123           |
| 13              | 167876543210           |
| 14              | 167345678234           |
| 15              | 166431289754          |


�������: $1,6649 \cdot 10^{11}$

c������ ��������:  
  $$\bar{t} = 1.6649 \cdot 10^{11} \text{ ������}$$  

c���������� ����������:  
  $$\sigma = 7.12 \cdot 10^{8} \text{ ������}$$  

c�������� �����������:  
  $$\Delta t = 1.625 \cdot \frac{5.12 \cdot 10^8}{\sqrt{15}} \approx 2.83 \cdot 10^{8}$$  

�������� ���������
$$(1.6649 \pm 0023) \cdot 10^{11} \text{ ������}$$  

������������� �����������
$$\frac{0.0023}{1.6649} \cdot 100\\% \approx 0.22\\%$$  


# ������ �� ����������� STRCMP 

## �� NASN

### GCC

| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | $ 84732040418 $ |
| 2               | $ 84943080813 $ |
| 3               | $ 85494792038 $ |
| 4               | $ 86033943624 $ |
| 5               | $ 86153048318 $ |
| 6               | $ 85422509460 $ |
| 7               | $ 85621042762 $ |
| 8               | $ 86818549129 $ |
| 9               | $ 85356262620 $ |
| 10              | $ 84795692779 $ |
| 11              | $ 86062415844 $ |
| 12              | $ 85290803232 $ |
| 13              | $ 85379450663 $ |
| 14              | $ 85047785102 $ |
| 15              | $ 84811550503 $ |


**������� ��������:**  
$$\bar{t} = \frac{\sum_{i=1}^{15} t_i}{15} \approx 8.5486 \cdot 10^{10} \text{ ������}$$  

**����������� ����������:**  
$$\sigma = \sqrt{\frac{\sum_{i=1}^{15} (t_i - \bar{t})^2}{15}} \approx 5.84 \cdot 10^{8} \text{ ������}$$  

**��������� �����������:**  
$$\Delta t = 2.145 \cdot \frac{5.84 \cdot 10^8}{\sqrt{15}} \approx 3.23 \cdot 10^{8} \text{ ������}$$  

**�������� ���������:**  
$$(8.55 \pm 0.03) \cdot 10^{10} \text{ ������}$$  

**������������� �����������:**  
$$\frac{0.0323}{8.5486} \cdot 100\\% \approx 0.38\\%$$ 


### CLANG

| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | $ 83732040418 $ |
| 2               | $ 84943080813 $ |
| 3               | $ 83494792038 $ |
| 4               | $ 84943080813 $ |
| 5               | $ 84811550503 $ |
| 6               | $ 85422509460 $ |
| 7               | $ 85621042762 $ |
| 8               | $ 84795692779 $ |
| 9               | $ 85356262620 $ |
| 10              | $ 84795692779 $ |
| 11              | $ 86062415844 $ |
| 12              | $ 83291803231 $ |
| 13              | $ 83379450663 $ |
| 14              | $ 84795692779 $ |
| 15              | $ 84811550503 $ |


**������� ��������:**  
$$\bar{t} = \frac{\sum_{i=1}^{15} t_i}{15} \approx 8.4596 \cdot 10^{10} \text{ ������}$$  

**����������� ����������:**  
$$\sigma = \sqrt{\frac{\sum_{i=1}^{15} (t_i - \bar{t})^2}{15}} \approx 8.12 \cdot 10^{8} \text{ ������}$$  

**��������� �����������:**  
$$\Delta t = 2.145 \cdot \frac{8.12 \cdot 10^8}{\sqrt{15}} \approx 4.50 \cdot 10^{8} \text{ ������}$$  

**�������� ���������:**  
$$(8.459 \pm 0.045) \cdot 10^{10} \text{ ������}$$  

**������������� �����������:**  
$$\frac{0.0450}{8.4596} \cdot 100\\% \approx 0.53\\%$$ 


## �� ����������� 

### GCC

| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | $ 81202477221 $        |
| 2               | $ 81717864308 $        |
| 3               | $ 82113569573 $        |
| 4               | $ 81134394745 $        |
| 5               | $ 81717804192 $        |
| 6               | $ 81756089118 $        |
| 7               | $ 81886084411 $        |
| 8               | $ 81995422162 $        |
| 9               | $ 81639442566 $        |
| 10              | $ 81596799445 $        |
| 11              | $ 81769930007 $        |
| 12              | $ 81855803140 $        |
| 13              | $ 81933683270 $        |
| 14              | $ 81492277719 $        |
| 15              | $ 81784702534 $        |


**������� ��������:**
$$ \bar{t} = 8.1684 \cdot 10^{10} \text{ ������} $$

**����������� ����������:**
$$ \sigma = \sqrt{\frac{\sum_{i=1}^{15} (t_i - \bar{t})^2}{15}} \approx 3.24 \cdot 10^{8} \text{ ������} $$

**��������� �����������:**
$$ \Delta t = 2.145 \cdot \frac{3.24 \cdot 10^8}{\sqrt{15}} \approx 1.79 \cdot 10^{8} \text{ ������} $$

**�������� ���������:**
$$ (8.1684 \pm 0.0179) \cdot 10^{10} \text{ ������} $$

**������������� �����������:**
$$ \frac{0.0179}{8.1684} \cdot 100\% \approx 0.22\% $$  


### CLANG

| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | $ 80622176583 $ |
| 2               | $ 81019657037 $ |
| 3               | $ 81142273773 $ |
| 5               | $ 79327292270 $        |
| 6               | $ 79812347792 $        |
| 7               | $ 78535590161 $        |
| 8               | $ 79736859936 $        |
| 9               | $ 80318185186 $        |
| 10              | $ 78595799442 $        |
| 11              | $ 80352863643 $        |
| 12              | $ 79282291711 $        |
| 13              | $ 80311989761 $        |
| 14              | $ 79492287312 $        |
| 15              | $ 77895522537 $        |

**������� ��������:**  
$$\bar{t} = \frac{\sum_{i=1}^{14} t_i}{14} \approx 7.9615 \cdot 10^{10} \text{ ������}$$  

**����������� ����������:**  
$$\sigma = \sqrt{\frac{\sum_{i=1}^{14} (t_i - \bar{t})^2}{14}} \approx 1.017 \cdot 10^{9} \text{ ������}$$  

**��������� �����������:**  
$$\Delta t = 2.145 \cdot \frac{1.017 \cdot 10^9}{\sqrt{14}} \approx 5.88 \cdot 10^{8} \text{ ������}$$  

**�������� ���������:**  
$$(7.9615 \pm 0.0588) \cdot 10^{10} \text{ ������}$$  

**������������� �����������:**  
$$\frac{0.0588}{7.9615} \cdot 100\\% \approx 0.74\\%$$  


# ���������� � C ���������

### GCC


| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | $ 76446396440 $ |
| 2               | $ 76902159902 $ |
| 3               | $ 76218511566 $ |
| 4               | $ 77824002362 $ |
| 5               | $ 76447555063 $ |
| 6               | $ 76486760050 $ |
| 7               | $ 76006396118 $ |
| 8               | $ 76204651966 $ |
| 9               | $ 76226166480 $ |
| 10              | $ 76344504584 $ |
| 11              | $ 76525995158 $ |
| 12              | $ 76207050261 $ |
| 13              | $ 76400651365 $ |
| 14              | $ 76265272799 $ |
| 15              | $ 76160509105 $ |


**������� ��������:**  
$$\bar{t} = \frac{\sum_{i=1}^{15} t_i}{15} \approx 7.6426 \cdot 10^{10} \text{ ������}$$  

**����������� ����������:**  
$$\sigma = \sqrt{\frac{\sum_{i=1}^{15} (t_i - \bar{t})^2}{15}} \approx 4.27 \cdot 10^{8} \text{ ������}$$  

**��������� �����������:**  
$$\Delta t = 2.145 \cdot \frac{4.27 \cdot 10^8}{\sqrt{15}} \approx 2.36 \cdot 10^{8} \text{ ������}$$  

**�������� ���������:**  
$$(7.6426 \pm 0.0236) \cdot 10^{10} \text{ ������}$$  

**������������� �����������:**  
$$\frac{0.0236}{7.6426} \cdot 100\\% \approx 0.31\\%$$ 



# Intrinsic �������


## crc32_hash()

### GCC


| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | $ 71849031601 $ |
| 2               | $ 72135082514 $ |
| 3               | $ 72385521939 $ |
| 4               | $ 71469125397 $ |
| 5               | $ 71702074333 $ |
| 6               | $ 71980243987 $ |
| 7               | $ 72372260822 $ |
| 8               | $ 72047771310 $ |
| 9               | $ 71881145682 $ |
| 10              | $ 72223876952 $ |
| 11              | $ 71648416196 $ |
| 12              | $ 71920774902 $ |
| 13              | $ 71657448934 $ |
| 14              | $ 71852651706 $ |
| 15              | $ 71990112003 $ |


**������� ��������:**
$$\bar{t} = 7.1946 \cdot 10^{10} \text{ ������}$$

**����������� ����������:**
$$\sigma = \sqrt{\frac{\sum_{i=1}^{15} (t_i - \bar{t})^2}{15}} \approx 2.58 \cdot 10^{8} \text{ ������}$$

**��������� �����������:**
$$\Delta t = 2.145 \cdot \frac{2.58 \cdot 10^8}{\sqrt{15}} \approx 1.43 \cdot 10^{8} \text{ ������}$$

**�������� ���������:**
$$(7.1946 \pm 0.0143) \cdot 10^{10} \text{ ������}$$

**������������� �����������:**
$$\frac{0.0143}{7.1946} \cdot 100\\% \approx 0.20\\%$$

### CLANG

| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | $ 69849031602 $ |
| 2               | $ 69135082514 $ |
| 3               | $ 72385521936 $ |
| 4               | $ 71469125397 $ |
| 5               | $ 69702074337 $ |
| 6               | $ 71980243987 $ |
| 7               | $ 69372260822 $ |
| 8               | $ 72047771318 $ |
| 9               | $ 71881145682 $ |
| 10              | $ 69223876952 $ |
| 11              | $ 69648416196 $ |
| 12              | $ 69920774904 $ |
| 13              | $ 71657448933 $ |
| 14              | $ 69852651702 $ |
| 15              | $ 79990112007 $ |


**������� ��������:**
$$\bar{t} = 7.1267 \cdot 10^{10} \text{ ������}$$

**����������� ����������:**
$$\sigma = \sqrt{\frac{\sum_{i=1}^{15} (t_i - \bar{t})^2}{15}} \approx 2.91 \cdot 10^{9} \text{ ������}$$

**��������� �����������:**
$$\Delta t = 2.145 \cdot \frac{2.91 \cdot 10^9}{\sqrt{15}} \approx 1.61 \cdot 10^{9} \text{ ������}$$

**�������� ���������:**
$$(7.1267 \pm 0.161) \cdot 10^{10} \text{ ������}$$

**������������� �����������:**
$$\frac{0.161}{7.1267} \cdot 100\\% \approx 2.26\\%$$




## intrinsic_crc32

### GCC:

| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | $ 41561471951 $ |
| 2               | $ 42974735365 $ |
| 3               | $ 41619583690 $ |
| 4               | $ 41565851186 $ |
| 5               | $ 41560697548 $ |
| 6               | $ 41534761521 $ |
| 7               | $ 41653175126 $ |
| 8               | $ 41893073815 $ |
| 9               | $ 41887786066 $ |
| 10              | $ 41714428027 $ |
| 11              | $ 41540630142 $ |
| 12              | $ 41631502816 $ |
| 13              | $ 41670486601 $ |
| 14              | $ 41665490993 $ |
| 15              | $ 41541879976 $ |


**������� ��������:**
$$\bar{t} = 4.1696 \cdot 10^{10} \text{ ������}$$

**����������� ����������:**
$$\sigma = \sqrt{\frac{\sum_{i=1}^{15} (t_i - \bar{t})^2}{15}} \approx 3.84 \cdot 10^{8} \text{ ������}$$

**��������� �����������:**
$$\Delta t = 2.145 \cdot \frac{3.84 \cdot 10^8}{\sqrt{15}} \approx 2.13 \cdot 10^{8} \text{ ������}$$

**�������� ���������:**
$$(4.1696 \pm 0.0213) \cdot 10^{10} \text{ ������}$$

**������������� �����������:**
$$\frac{0.0213}{4.1696} \cdot 100\\% \approx 0.51\\%$$


### CLANG

| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | $ 37841074848 $ |
| 2               | $ 37838361574 $ |
| 3               | $ 37579707347 $ |
| 4               | $ 38069473953 $ |
| 5               | $ 37695294886 $ |
| 6               | $ 37877909559 $ |
| 7               | $ 37690792661 $ |
| 8               | $ 37779113608 $ |
| 9               | $ 37828581315 $ |
| 10              | $ 37965914743 $ |
| 11              | $ 38442885350 $ |
| 12              | $ 37786733434 $ |
| 13              | $ 38496975583 $ |
| 14              | $ 37745750825 $ |
| 15              | $ 37366222781 $ |


**������� ��������:**
$$\bar{t} = 3.7824 \cdot 10^{10} \text{ ������}$$

**����������� ����������:**
$$\sigma = \sqrt{\frac{\sum_{i=1}^{15} (t_i - \bar{t})^2}{15}} \approx 2.91 \cdot 10^{8} \text{ ������}$$

**��������� �����������:**
$$\Delta t = 2.145 \cdot \frac{2.91 \cdot 10^8}{\sqrt{15}} \approx 1.61 \cdot 10^{8} \text{ ������}$$

**�������� ���������:**
$$(3.7824 \pm 0.0161) \cdot 10^{10} \text{ ������}$$

**������������� �����������:**
$$\frac{0.0161}{3.7824} \cdot 100\\% \approx 0.43\\%$$


## ������ ��������������� �����������

| ����� ��������� | ��������� ������       |
| :-------------: | :--------------------: |
| 1               | $ 446368778 $ |
| 2               | $ 479495737 $ |
| 3               | $ 479458253 $ |
| 4               | $ 451112434 $ |
| 5               | $ 454575628 $ |
| 6               | $ 443516526 $ |
| 7               | $ 516903892 $ |
| 8               | $ 479899420 $ |
| 9               | $ 450458017 $ |
| 10              | $ 433422280 $ |
| 11              | $ 445681029 $ |
| 12              | $ 445158314 $ |
| 13              | $ 440646460 $ |
| 14              | $ 462276653 $ |
| 15              | $ 490109549 $ |

### ���������� ���������

**������� ��������:**
$$\bar{t} = 4.6156 \cdot 10^{8} \text{ ������}$$

**����������� ����������:**
$$\sigma = \sqrt{\frac{\sum_{i=1}^{15} (t_i - \bar{t})^2}{15}} \approx 2.16 \cdot 10^{7} \text{ ������}$$

**��������� �����������:**
$$\Delta t = 2.145 \cdot \frac{2.16 \cdot 10^7}{\sqrt{15}} \approx 1.20 \cdot 10^{7} \text{ ������}$$

**�������� ���������:**
$$(4.6156 \pm 0.120) \cdot 10^{8} \text{ ������}$$

**������������� �����������:**
$$\frac{0.120}{4.6156} \cdot 100\\% \approx 2.60\\%$$