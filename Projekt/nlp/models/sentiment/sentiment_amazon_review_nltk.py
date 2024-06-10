import nltk
import sys
from nltk.sentiment.vader import SentimentIntensityAnalyzer
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
from nltk.stem import WordNetLemmatizer
from sklearn.metrics import confusion_matrix, classification_report
import pandas as pd
import os
import dill as pickle

def load_model(filename):
  with open(filename, 'rb') as file:
    sentiment_model = pickle.load(file)
    return sentiment_model

def save_model(filename, sentiment_model):
  with open(filename, 'wb') as file:
    pickle.dump(sentiment_model, file)

def preprocess(text):
    tokens = word_tokenize(text.lower())
    filtered_tokens = [token for token in tokens if token not in stopwords.words('english')]
    lemmatizer = WordNetLemmatizer()
    lemmatized_tokens = [lemmatizer.lemmatize(token) for token in filtered_tokens]
    processed_text = ' '.join(lemmatized_tokens)
    return processed_text


def get_sentiment(text, analyzer):
    scores = analyzer.polarity_scores(text)
    sentiment = 1 if scores['pos'] > 0 else 0
    return sentiment


def analyze(text):
    if os.path.exists("models/sentiment/sentiment_model.pkl"):
        # print("Model found, loading model...")
        analyzer = load_model("models/sentiment/sentiment_model.pkl")
    else: 
        # print("Model not found, training model...")
        nltk.download('punkt')
        nltk.download('vader_lexicon')
        nltk.download('stopwords')
        nltk.download('wordnet')
        analyzer = SentimentIntensityAnalyzer()
        df = pd.read_csv('https://raw.githubusercontent.com/pycaret/pycaret/master/datasets/amazon.csv')
        df['reviewText'] = df['reviewText'].apply(preprocess)
        df['sentiment'] = df['reviewText'].apply(lambda x: get_sentiment(x, analyzer))


        save_model("models/sentiment/sentiment_model.pkl", analyzer)

    s1 = preprocess(text)
    score = analyzer.polarity_scores(s1)
    # return [("Positive" if score['pos'] > 0 else "Negative"), str(0.5+(score['compound']/2))]
    return ("Positive" if score['pos'] > 0 else "Negative") + "\07" + str(0.5+(score['compound']/2))

# print(analyze("I love this film!"))
print(analyze(sys.argv[1]))