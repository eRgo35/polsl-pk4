import sys
from langdetect import detect

def detect_language(text):
  try:
    return detect(text)
  except Exception as e:
    return f"Error detecting language: {str(e)}"
  
print(detect_language(sys.argv[1]), end="")