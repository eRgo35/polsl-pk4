from transformers import pipeline

def translate_text_dummy(data):
    model_checkpoint = "Helsinki-NLP/opus-mt-pl-en"
    translator = pipeline("translation", model=model_checkpoint)
    
    translated = translator(data)
    
    return translated

def sentiment_analyze_dummy(data):
    classifier = pipeline("sentiment-analysis")
    res = classifier(data)
    
    return res