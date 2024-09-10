const gameContainer = document.getElementById('game-container');
const scoreDisplay = document.getElementById('score');
const progressFill = document.getElementById('progress-fill');
const cardValues = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'];
let flippedCards = [];
let matchedPairs = 0;
let score = 0;
const maxScore = cardValues.length / 2 * 10; // Maximum score when all pairs are matched

function createCard(value) {
    const card = document.createElement('div');
    card.className = 'card';
    card.innerHTML = `
        <div class="card-inner">
            <div class="card-front"></div>
            <div class="card-back">${value}</div>
        </div>
    `;
    card.dataset.value = value;
    card.addEventListener('click', flipCard);
    return card;
}

function shuffleArray(array) {
    for (let i = array.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [array[i], array[j]] = [array[j], array[i]];
    }
}

function setupGame() {
    shuffleArray(cardValues);
    cardValues.forEach(value => {
        const card = createCard(value);
        gameContainer.appendChild(card);
    });
}

function flipCard() {
    if (flippedCards.length === 2 || this.classList.contains('flipped') || this.classList.contains('matched')) return;

    this.classList.add('flipped');
    flippedCards.push(this);

    if (flippedCards.length === 2) {
        setTimeout(checkMatch, 600);  // Ensure this timeout matches the flip animation duration
    }
}

function checkMatch() {
    const [card1, card2] = flippedCards;

    if (card1.dataset.value === card2.dataset.value) {
        card1.classList.add('matched');
        card2.classList.add('matched');
        matchedPairs++;
        updateScore(); // Update score when a match is found
        if (matchedPairs === cardValues.length / 2) {
            setTimeout(() => alert('Congratulations! You found all pairs!'), 100);
        }
    } else {
        card1.classList.remove('flipped');
        card2.classList.remove('flipped');
    }

    flippedCards = [];
}

function updateScore() {
    score += 10; // Increase score by 10 for each matched pair
    scoreDisplay.textContent = score;
    const progressPercentage = (score / maxScore) * 100; // Calculate the percentage of the progress bar
    progressFill.style.width = `${progressPercentage}%`;
}

setupGame();
