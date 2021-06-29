# **NPRACH DETECTOR** :

**NOTE : Currently C code is Tested and working for CVA : 3, PRM : 0**

**TODO : Test and verify the results for other test cases**

***

## **TEST CASES** :

| Coverage area | Preamble format | Comments     |
|---------------|-----------------|--------------|
| 3             | 0               | Working      |
| 3             | 1               | To be tested |
| 2             | 0               | To be tested |
| 2             | 1               | To be tested |
| 1             | 0               | To be tested |
| 1             | 1               | To be tested |

***

## **RELEASE DETAILS** :

| Release version | Release date | Comments                                        |  
|-----------------|--------------|-------------------------------------------------|
| 1.0             | 29/06/2021   | CVA: 3, PRM : 0 Test case<br>Tested and working |

***

## **INSTRUCTIONS/DETAILS** :

1. **NPRACH_C** : Contains _**C**_ implementation of **NPRACH DETECTOR**

   * **Sample_Test_Data**    : Contains test data sampled from **_Test_data_** folder

   * **Sample_Test_Results** : Contains results produced from C code for the data in **_Sample_Test_Data_** folder

   * **main.c**              : For verification of results from C code

                              Choose Coverage area: CVA and Preamble format : PRM

                              Choose any data file ending with **xx** (xx :[1 - 100])from the _Test_Data_ folder corresponding to chosen CVA and PRM

                              Replace '1' by 'xx' in file includes of 'main.c' and 'NPRACH_DETECTOR_PRM0_Fixed.c'

                              Run the code, results will be stored in _Sample_Test_Results_ folder corresponding to chosen CVA and PRM

                              Results can be verified by comparing it with the sheet **xx** of 'Results_PRM0.xls' or 'Results_PRM1.xls' based on chosen PRM


2. **NPRACH_M** : Contains _**Matlab**_ implementation of **NPRACH DETECTOR**

   * **Results_PRM0.xls** : Contains results produced from Matlab code for data in **_Test_Data_** folder corresponding to preamble format 0 in different sheets

   * **Results_PRM1.xls** : Contains results produced from Matlab code for data in **_Test_Data_** folder corresponding to preamble format 1 in different sheets

   * **MainSystem.m**     : Run this file to produce **'Results_PRM0.xls'** or **'Results_PRM1.xls'** based on Preamble format


3. **Test_Data**: Contains test data and corresponding true values for all possible test cases (100 data  for each test case)
