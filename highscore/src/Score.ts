interface IScore {
  score: number;
  name: string;
  photograph: string;
  image: string;
  timestamp: number;
}

class Score {
  constructor(public data: IScore) {};
}

export { IScore, Score };
