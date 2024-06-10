import sys
from presidio_analyzer import AnalyzerEngine

def anonymize_data(text):
    analyzer = AnalyzerEngine()
    
    results = analyzer.analyze(text=text, entities=[], language='en')    
    results = sorted(results, key=lambda x: x.start)

    merged_results = []
    for result in results:
        if merged_results and merged_results[-1].end >= result.start - 1:
            merged_results[-1].end = max(merged_results[-1].end, result.end)
        else:
            merged_results.append(result)
    
    anonymized_text = text
    for result in reversed(merged_results): 
        anonymized_text = anonymized_text[:result.start] + '[REDACTED]' + anonymized_text[result.end:]
    
    return anonymized_text
 
print(anonymize_data(sys.argv[1]))

# print(anonymize_data("John Doe's phone number is 123-456-7890 and his email is johndoe@example.com."))
# print(anonymize_data("Numer telefonu Michała Czyża to +48 123 456 789 i jego email to mike@c2yz.com."))