#ifndef SENTIMENTCALCULATION_HPP
#define SENTIMENTCALCULATION_HPP

class SentimentCalculation {
public:
    // Function to calculate the raw sentiment score (Positive count - Negative count)
    static int calculateRawSentiment(int positiveCount, int negativeCount);

    // Function to calculate the normalized sentiment score
    static double calculateNormalizedScore(int rawScore, int N);

    // Function to convert normalized score to a sentiment score from 1 to 5
    static double calculateSentimentScore(int positiveCount, int negativeCount);
};

#endif
