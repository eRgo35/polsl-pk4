import sys
from transformers import pipeline
from transformers import AutoTokenizer, TFAutoModelForSequenceClassification
classifier = pipeline("sentiment-analysis", model=TFAutoModelForSequenceClassification.from_pretrained("distilbert/distilbert-base-uncased-finetuned-sst-2-english"), tokenizer = AutoTokenizer.from_pretrained("distilbert/distilbert-base-uncased-finetuned-sst-2-english"))

def analyze(data):
    # print("Running pipeline sentiment-analysis with data: ", data)
    res = classifier(data)
    decision = res[0]['label']
    score = res[0]['score']
    # return [decision, score]
    return decision + "\07" + str(score)

print(analyze(sys.argv[1]))