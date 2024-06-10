import pandas as pd
import re
import sys
import dill as pickle
import os
from nltk.translate import AlignedSent, IBMModel1
import datasets as ds

def load_data(df, amount=1.0):
  sample_size = int(len(df) * amount)

  df = df.sample(n=sample_size, random_state=42)

  english_sentences = df[0].astype(str).tolist()
  polish_sentences = df[1].astype(str).tolist()

  print(f"Sentences in English: {len(english_sentences)}")
  print(f"Sentences in Polish: {len(polish_sentences)}")
  print(english_sentences[0], "\t", polish_sentences[0])

  return english_sentences, polish_sentences

def load_dataset(name):
  dataset = ds.load_dataset(name, lang1="en", lang2="pl", split="train")
  dataset = dataset.shuffle(seed=100)

  english_sentences = [row['translation']['en'] for row in dataset]
  polish_sentences = [row['translation']['pl'] for row in dataset]

  print(f"Sentences in English: {len(english_sentences)}")
  print(f"Sentences in Polish: {len(polish_sentences)}")
  
  # for i in range(100):
    # print(english_sentences[i], "\t", polish_sentences[i])

  return english_sentences, polish_sentences

def load_model(filename):
  with open(filename, 'rb') as file:
    translation_model = pickle.load(file)
    return translation_model

def save_model(filename, translation_model):
  with open(filename, 'wb') as file:
    pickle.dump(translation_model, file)

def clean_text(text):
  clean_text = []

  for sentence in text:
    sentence = sentence.strip().lower()
    sentence = re.sub(r"[^a-zA-Z0-9ĘÓĄŚŁŻŹĆŃęóąśłżźćń]+", ' ', sentence)
    clean_text.append(sentence.strip())
  
  return clean_text

def train_model(src, dst):
  aligned_sentences = [AlignedSent(source.split(), target.split()) for source, target in zip(src, dst)]
  ibm_model = IBMModel1(aligned_sentences, 10)
  return ibm_model

def translate(text, model):
  cleaned_text = clean_text(text.split())  
  # print(cleaned_text)

  source_words = cleaned_text
  translated_words = []

  for source_word in source_words:
    max_prob = 0.0
    translated_word = None

    for target_word in model.translation_table[source_word]:
      prob = model.translation_table[source_word][target_word]
      if prob > max_prob:
        max_prob = prob
        translated_word = target_word
    
    if translated_word is not None:
      translated_words.append(translated_word)
  
  translated_text = " ".join(translated_words)

  return translated_text

def smt_translate(prompt):
  if os.path.exists("models/translation/translation_model.pkl"):
    # print("Model found, loading model...")
    translation_model = load_model("models/translation/translation_model.pkl")
  else:
    # print("Model not found, training model...")

    df = pd.read_csv("models/datasets/pol.csv", sep=';', header=None)
    # df = pd.read_csv("../datasets/EN-PL.txt", sep='\t', header=None)
    english_sentences, polish_sentences = load_data(df)
    # english_sentences, polish_sentences = load_dataset("kde4")

    cleaned_english_sentences = clean_text(english_sentences)
    cleaned_polish_sentences = clean_text(polish_sentences)

    print(cleaned_english_sentences[0], "\t", cleaned_polish_sentences[0])

    translation_model = train_model(cleaned_english_sentences, cleaned_polish_sentences)
    save_model("models/translation/translation_model.pkl", translation_model)

  # print("Model loaded successfully!")

  result = translate(prompt, translation_model)
  return result

# print(smt_translate("Computer programming is really fun!"))
print(smt_translate(sys.argv[1]))

