
# Natural Language Processing ||

# N-gram Tutorial: In-depth Intuition in NLP

This repository contains resources and insights from the N-gram tutorial by Krish Naik, focused on providing an in-depth understanding of N-grams in Natural Language Processing (NLP). The tutorial is presented in Hindi and covers various aspects of N-grams, including their significance, applications, and implementation.

## Overview

N-grams are contiguous sequences of n items (words, characters, etc.) from a given text or speech. They are a fundamental concept in NLP and are widely used in language modeling, text classification, and other applications.

### Key Concepts Covered

- **Definition of N-grams**: Understanding what N-grams are and how they are formed.
- **Types of N-grams**: 
  - Unigrams (1-grams)
  - Bigrams (2-grams)
  - Trigrams (3-grams)
  - Higher-order N-grams
- **Applications**: How N-grams are used in various NLP tasks, such as text prediction, sentiment analysis, and machine translation.
- **Implementation**: Practical examples of how to implement N-grams in Python.

## Video Tutorial

For a comprehensive understanding of N-grams, watch the tutorial by Krish Naik:

[In-depth Intuition on N-grams in NLP (Hindi)](https://www.youtube.com/watch?v=VIDEO_ID)

## Usage

To create N-grams from a given text, you can follow these steps:

1. Preprocess the text (tokenization, lowercasing, etc.).
2. Choose the value of n for the N-gram (e.g., 1 for unigrams, 2 for bigrams).
3. Generate the N-grams from the tokenized text.

### Example Code

Here's a simple example of how to generate N-grams in Python:

```python
from nltk import ngrams
from collections import Counter

def generate_ngrams(text, n):
    tokens = text.split()  # Basic tokenization
    n_grams = ngrams(tokens, n)
    return Counter(n_grams)

# Example usage
text = "I love natural language processing"
bigrams = generate_ngrams(text, 2)
print(bigrams)
```

# Laplace Smoothing in NLP

Laplace smoothing, also known as additive smoothing, is a technique used in statistics and machine learning to address zero-frequency problems in categorical data. It ensures that events that have not been observed in the training data are assigned a non-zero probability, thereby preventing the assignment of zero probabilities to unseen events.

In Natural Language Processing (NLP), Laplace smoothing is particularly useful when dealing with language models, especially Naive Bayes classifiers. By applying this technique, we can improve the model's performance on unseen data and avoid issues related to overfitting.

## Key Concepts

- **Zero-Frequency Problem**: This occurs when an event (e.g., a word) does not appear in the training dataset, leading to a probability of zero for that event.
- **Additive Smoothing**: By adding a small constant (usually 1) to the counts of each event, we can ensure that no event has a zero probability.

## Video Tutorial

For a comprehensive understanding of Laplace smoothing, you might find the following video helpful:

[Mastering Laplace Smoothing in Naive Bayes: Avoiding Overfitting](https://www.youtube.com/watch?v=mmguq4BHVCc)

## Usage

To implement Laplace smoothing in your NLP projects, consider the following steps:

1. Calculate the frequency of each event in your training data.
2. Apply Laplace smoothing by adding 1 (or a small constant) to each frequency count.
3. Normalize the counts to obtain probabilities.

## Example

Here's a simple example of how to apply Laplace smoothing in Python:

```python
def laplace_smoothing(counts, vocab_size):
    smoothed_counts = {word: count + 1 for word, count in counts.items()}
    total_counts = sum(smoothed_counts.values())
    return {word: count / total_counts for word, count in smoothed_counts.items()}

# Example usage
counts = {'word1': 5, 'word2': 0, 'word3': 3}
vocab_size = len(counts)
smoothed_probs = laplace_smoothing(counts, vocab_size)
print(smoothed_probs)
```

# Naive Bayes Classification: In-depth Intuition

Naive Bayes is a family of probabilistic classifiers based on Bayes' Theorem, assuming that the features used for classification are independent of each other given the class label. This "naive" assumption simplifies the computation of probabilities and allows for efficient classification.

1. **Gaussian Naive Bayes**: Used for continuous data assuming a normal distribution.
2. **Multinomial Naive Bayes**: Suitable for discrete data (e.g., word counts for text classification).
3. **Bernoulli Naive Bayes**: Used for binary/boolean features (presence/absence of features).

Here's a complete code example showcasing all three types of Naive Bayes classifiers:

```python
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import GaussianNB, MultinomialNB, BernoulliNB
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

# Sample dataset for text classification
data = {
    'message': [
        'Hey, how are you?',
        'Win a $1000 cash prize now!',
        'Hello, let’s meet for lunch tomorrow.',
        'Congratulations! You have won a lottery.',
        'Your appointment is confirmed.',
        'Click this link to claim your prize!',
        'See you at the party tonight.',
        'Get paid to work from home!',
        'This is a great deal!',
        'Limited time offer just for you!',
    ],
    'label': [
        'ham',
        'spam',
        'ham',
        'spam',
        'ham',
        'spam',
        'ham',
        'spam',
        'ham',
        'spam',
    ]
}

# Create a DataFrame
df = pd.DataFrame(data)

# Step 3: Preprocess the Data
X = df['message']  # Features
y = df['label']    # Labels

# Split the dataset into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=42)

# Step 4: Vectorization for Multinomial and Bernoulli Naive Bayes
vectorizer = CountVectorizer(binary=False)  # Use binary=False for MultinomialNB
X_train_vectorized = vectorizer.fit_transform(X_train)
X_test_vectorized = vectorizer.transform(X_test)

# Step 5: Multinomial Naive Bayes
multinomial_model = MultinomialNB()
multinomial_model.fit(X_train_vectorized, y_train)
y_pred_multinomial = multinomial_model.predict(X_test_vectorized)

# Step 6: Evaluate Multinomial Naive Bayes
accuracy_multinomial = accuracy_score(y_test, y_pred_multinomial)
conf_matrix_multinomial = confusion_matrix(y_test, y_pred_multinomial)
class_report_multinomial = classification_report(y_test, y_pred_multinomial)

print("Multinomial Naive Bayes Results:")
print(f'Accuracy: {accuracy_multinomial}')
print('Confusion Matrix:')
print(conf_matrix_multinomial)
print('Classification Report:')
print(class_report_multinomial)

# Step 7: Bernoulli Naive Bayes (for binary features)
vectorizer_b = CountVectorizer(binary=True)  # Use binary=True for BernoulliNB
X_train_vectorized_b = vectorizer_b.fit_transform(X_train)
X_test_vectorized_b = vectorizer_b.transform(X_test)

bernoulli_model = BernoulliNB()
bernoulli_model.fit(X_train_vectorized_b, y_train)
y_pred_bernoulli = bernoulli_model.predict(X_test_vectorized_b)

# Step 8: Evaluate Bernoulli Naive Bayes
accuracy_bernoulli = accuracy_score(y_test, y_pred_bernoulli)
conf_matrix_bernoulli = confusion_matrix(y_test, y_pred_bernoulli)
class_report_bernoulli = classification_report(y_test, y_pred_bernoulli)

print("\nBernoulli Naive Bayes Results:")
print(f'Accuracy: {accuracy_bernoulli}')
print('Confusion Matrix:')
print(conf_matrix_bernoulli)
print('Classification Report:')
print(class_report_bernoulli)

# Step 9: Gaussian Naive Bayes (requires numerical data)
# For demonstration, let's create a synthetic dataset with numerical features
X_numeric = np.array([[1, 2], [1, 4], [1, 0],
                      [2, 2], [2, 4], [2, 0],
                      [0, 0], [0, 1], [0, 2],
                      [3, 3], [3, 4], [3, 0]])
y_numeric = np.array(['ham', 'ham', 'ham', 'spam', 'spam', 'spam', 
                      'ham', 'ham', 'ham', 'spam', 'spam', 'spam'])

# Split numeric dataset
X_train_num, X_test_num, y_train_num, y_test_num = train_test_split(X_numeric, y_numeric, test_size=0.25, random_state=42)

# Step 10: Gaussian Naive Bayes
gaussian_model = GaussianNB()
gaussian_model.fit(X_train_num, y_train_num)
y_pred_gaussian = gaussian_model.predict(X_test_num)

# Step 11: Evaluate Gaussian Naive Bayes
accuracy_gaussian = accuracy_score(y_test_num, y_pred_gaussian)
conf_matrix_gaussian = confusion_matrix(y_test_num, y_pred_gaussian)
class_report_gaussian = classification_report(y_test_num, y_pred_gaussian)

print("\nGaussian Naive Bayes Results:")
print(f'Accuracy: {accuracy_gaussian}')
print('Confusion Matrix:')
print(conf_matrix_gaussian)
print('Classification Report:')
print(class_report_gaussian)
```




### Key Concepts

- **Bayes' Theorem**: The foundation of Naive Bayes, which describes the probability of a class based on prior knowledge of conditions related to the class:
  
  \[
  P(A|B) = \frac{P(B|A) \cdot P(A)}{P(B)}
  \]

  Where:
  - \(P(A|B)\): Posterior probability of class A given feature B.
  - \(P(B|A)\): Likelihood of feature B given class A.
  - \(P(A)\): Prior probability of class A.
  - \(P(B)\): Total probability of feature B.

- **Types of Naive Bayes**:
  - **Gaussian Naive Bayes**: Assumes that the features follow a normal (Gaussian) distribution.
  - **Multinomial Naive Bayes**: Used for discrete features, particularly useful for text classification tasks where the features represent word counts.
  - **Bernoulli Naive Bayes**: Similar to Multinomial, but assumes binary features (presence or absence of a feature).

- **Applications**:
  - **Spam Detection**: Classifying emails as spam or not spam.
  - **Sentiment Analysis**: Determining the sentiment of product reviews or social media posts.
  - **Document Classification**: Categorizing documents into predefined topics based on their content.

## Video Tutorials

For a comprehensive understanding of Naive Bayes, you might find the following videos helpful:

1. **Naive Bayes Machine Learning Algorithm - In-depth Intuition**
   [Watch here](https://youtu.be/7zpEuCTcdKk?si=u8IYCWYI47lwpi5M)

2. **Naïve Bayes Classification Problem - Numerical Solved Example**
   [Watch here](https://youtu.be/VIj6xS937E4?si=NlOyg7X1vifqMWuv) by Mahesh Huddar

3. **Solved Example: Using Naive Bayes Classifier to Classify Color, Legs, Height, Smelly**
   [Watch here](https://youtu.be/vum--8Slq_E?si=XcASlR4t9n3TWVuZ) by Mahesh Huddar

4. **Solved Example: Naive Bayes Classifier to Classify New Instance**
   [Watch here](https://youtu.be/QPvHY9t1Ouw?si=7veZ9kHmwaCEhCfb) by Mahesh Huddar

5. **Naive Bayes Theorem: Solved Example**
   [Watch here](https://youtu.be/yRl8Yq0M3TY?si=vLFBUS_B7mRO9dlD) by Mahesh Huddar

6. **Text Classification: Spam Classification Using Naive Bayes Classifier (Add Smoothing)**
   [Watch here](https://youtu.be/YcsDbCvRBxg?si=TGaBACHpz0zy2cMg) by Mahesh Huddar


