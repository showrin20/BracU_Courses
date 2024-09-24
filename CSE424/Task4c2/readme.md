# Task 4c2
# EuroSAT before Pre-Processing 
[Dataset before pre-processing](https://paperswithcode.com/dataset/eurosat)
[github](https://github.com/phelber/eurosat)


# EuroSAT before Pre-Processing 

[Pre-processing with EDA](https://github.com/showrin20/BracU_Courses/blob/main/CSE424/Task4/cse424_EUROSAT%2BEDA.ipynb)

## Exploratory Data Analysis (EDA) Steps

### **PRE-EXPLORATORY ANALYSIS:**
1. **Data Distribution in Classes**  
   Analyzing the number of images across different classes.

2. **Visualizing Sample Images**  
   Random visualization of images from each class to ensure data integrity and correct loading.

3. **Pixel Intensity Analysis**  
   Checking pixel intensity (sum, mean, median) of sample images.

4. **Correlation Between Channels**  
   Visualizing and analyzing correlation between RGB channels.



### **POST-EXPLORATORY ANALYSIS:**
1. **Data Distribution in Classes**  
   Ensuring data distribution remains consistent post-processing.

2. **Normalizing and Transforming Images**  
   Normalizing pixel values from 0-255 to 0-1 and applying random transformations (resize, flip, etc.).

3. **RGB Distribution**  
   Visualizing RGB distribution on transformed images.

4. **Image Ratio Distribution**  
   Ensuring image height and width remain constant after transformations.

5. **Correlation Between Channels**  
   Re-checking correlation between RGB channels post-normalization.

6. **Post-Process Pixel Intensity Distribution**  
   Analyzing pixel intensity distribution after normalization.

7. **Data Augmentation**  
   Applying data augmentation techniques using PyTorch’s `permute()` for tensor manipulation.

