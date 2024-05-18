from transformers import pipeline

def translate_text_dummy(data):
    model_checkpoint = "Helsinki-NLP/opus-mt-en-fr"
    translator = pipeline("translation", model=model_checkpoint)
    
    
    translator("Default to expanded threads")
    
    return "Witaj świecie!"

def sentiment_analyze_dummy(data):

    return True