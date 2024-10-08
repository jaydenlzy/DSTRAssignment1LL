#include "SentimentCalculation.h"

// Function to calculate the raw sentiment score (Positive count - Negative count)
int SentimentCalculation::calculateRawSentiment(int positiveCount, int negativeCount) {
    return positiveCount - negativeCount;
}

// Function to calculate the normalized sentiment score
double SentimentCalculation::calculateNormalizedScore(int rawScore, int N) {
    int minRawScore = -N;
    int maxRawScore = N;

    // Normalized score based on min and max raw score
    return static_cast<double>(rawScore - minRawScore) / (maxRawScore - minRawScore);
}

// Function to convert normalized score to a sentiment score from 1 to 5
double SentimentCalculation::calculateSentimentScore(int positiveCount, int negativeCount) {
    int N = positiveCount + negativeCount;
    if (N == 0) {
        // If no positive or negative words, return a neutral score of 3
        return 3.0;
    }

    int rawScore = calculateRawSentiment(positiveCount, negativeCount);
    double normalizedScore = calculateNormalizedScore(rawScore, N);

    // Sentiment score is between 1 and 5
    return 1 + (4 * normalizedScore);
}
