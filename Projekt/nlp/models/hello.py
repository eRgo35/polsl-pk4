import sys
sys.path.append('/home/mike/Projects/nlp-platform/nlp/models')

from sentiment.sentiment_amazon_review_nltk import analyze as analyze_nltk
# from sentiment.sentiment_film_review_pipeline import analyze as analyze_pipeline

# from anonimize import anonymize_data

from translation.ct2 import ct2_translate
# from translation.detect import detect_language
# from translation.mt5 import mt5_translate
# from translation.opus import opus_translate
# from translation.smt import smt_translate

def call_python(function_name, *args):
    function = globals()[function_name]
    response = function(*args)
    return response

def stringlist():
    return ["foo", "bar", "baz"]

if __name__ == "__main__":
    print("This is a python script")
    print("It's running within a C++ program.")
    # print(call_python("ct2_translate", "it", "I love pizza!"))